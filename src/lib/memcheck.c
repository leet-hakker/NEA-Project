#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../../include/memcheck.h"
#include <stdint.h>
#include <gint/fs.h>
#include <gint/bfile.h>
#include <gint/keyboard.h>
#ifndef FXCG50
#define FXCG50
#endif
#include <gint/display.h>

size_t num_length(size_t number) {
	if (number == 0) {
		return 1;
	} else {
		return floor(log10(abs(number))) + 1;
	}
}

typedef struct AllocRecord {
	size_t size;
	const char* file;
	int line;
	const char* func;
	void* address;
	struct AllocRecord* next;
} AllocRecord;

static void* (*real_malloc)(size_t) = malloc;
static void* (*real_calloc)(size_t, size_t) = calloc;
static void* (*real_realloc)(void*, size_t) = realloc;
static void (*real_free)(void*) = free;

static AllocRecord* records = NULL;		// A linked list, hold all allocation records

/* Add a record into records */
static AllocRecord* add_record(size_t size, const char* file, int line, const char* func, void* address) {
	AllocRecord* record = (AllocRecord*)real_malloc(sizeof(AllocRecord));
	record->size = size;
	record->file = file;
	record->line = line;
	record->func = func;
	record->address = address;
	record->next = NULL;
	record->next = records;
	records = record;
	return record;
}

void* _memcheck_malloc(size_t size, const char* file, int line, const char* func) {
	return add_record(size, file, line, func, real_malloc(size))->address;
}

void* _memcheck_calloc(size_t num, size_t size, const char* file, int line, const char* func) {
	return add_record(size * num, file, line, func, real_calloc(num, size))->address;
}

void* _memcheck_realloc(void* ptr, size_t size, const char* file, int line, const char* func) {
	// Remove the record of the original ptr in records first

	AllocRecord* cur = records;
	AllocRecord* pre = NULL;

	while(cur != NULL) {
		if(cur->address == ptr) {
			if(pre != NULL)
				pre->next = cur->next;
			else
				records = cur->next;

			real_free(cur);
			break;
		}

		pre = cur;
		cur = cur->next;
	}

	return add_record(size, file, line, func, real_realloc(ptr, size))->address;
}

void _memcheck_free(void* ptr) {
	AllocRecord* cur = records;
	AllocRecord* pre = NULL;

	while(cur != NULL) {
		if(cur->address == ptr) {
			if(pre != NULL)
				pre->next = cur->next;
			else
				records = cur->next;

			real_free(ptr);
			real_free(cur);
			break;
		}

		pre = cur;
		cur = cur->next;
	}
}

void memcheck() {
	AllocRecord* cur = records;
	AllocRecord* pre = NULL;

	fs_descriptor_type_t desc_type;

	int size = 10000;

	uint16_t const *path = u"\\\\fls0\\PERF";

	BFile_Remove(path);
	int rc = BFile_Create(path, BFile_File, &size);

	if (rc < 0) {
		dclear(0xFFFF);
		dtext(1, 1, 0x0000, "Failed to create file.");
		dupdate();
		getkey();
		return;
	}

	int fd = BFile_Open(path, BFile_WriteOnly);

	if(cur == NULL) {
		BFile_Write(fd, "No memory leak", 16);
		BFile_Close(fd);
		return;
	}

	BFile_Write(fd, "Memory leaks:\n", 18);

	while(cur != NULL) {
		char *str = malloc(38 + num_length(cur->size) + sizeof(cur->address) + strlen(cur->file) + num_length(cur->line) + strlen(cur->func));
		sprintf(str, "  %llu bytes at 0x%p (allocate from %s:%d in %s)\n", cur->size, cur->address, cur->file, cur->line, cur->func);
		BFile_Write(fd, str, (strlen(str)+1)+(strlen(str)+1)%2);
		pre = cur;
		cur = cur->next;
		real_free(pre);
	}

	BFile_Close(fd);
}
