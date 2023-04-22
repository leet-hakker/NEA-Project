#include <gint/display.h>
#include <gint/keyboard.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/fraction.h"
#include "../include/bigm.h"
#include "../include/matrix.h"
#include "../include/simplex.h"
#include "../include/tableux.h"
#include "../include/input.h"
#include "../include/stages.h"


Tableux *tableux_construction_stage() {
	VisualCell *row_number_cell = new_viscell(80, 70, 80, 30, true, "4");
	VisualCell *column_number_cell = new_viscell(260, 70, 80, 30, false, "5");

	bool exit = false;

	while (!exit) {
		dtext(10, 85, 0x0000, "Rows:");
		dtext(200, 85, 0x0000, "Cols:");
		draw_cell(row_number_cell);
		draw_cell(column_number_cell);
		dupdate();
		key_event_t key = getkey();
		exit = process_key_construction_stage(key, row_number_cell, column_number_cell);
	}

	uint8_t row_num = atoi(row_number_cell->contents);
	uint8_t column_num = atoi(column_number_cell->contents);

	free_viscell(row_number_cell);
	free_viscell(column_number_cell);

	Tableux *tab = new_tableux(row_num, column_num);

	return tab;
}

int tableux_input_stage(Tableux *tab) {
	key_event_t key;
	uint8_t cursor_x = 1;
	uint8_t cursor_y = 0;
	uint8_t stage = 0;

	while (true) {
		display_tableux(tab);

		dupdate();

		dclear(0xffff);

		key = getkey();

		if (key.key == 0x84)
			break;

		switch (stage) {
			case 0:
				if (process_key_rowcol_stage(key, &cursor_x, &cursor_y, tab)) {
					stage = 1;
				}
				break;
			
			case 1:
				if (process_key_tableux_stage(key, &cursor_x, &cursor_y, tab)) {
					stage = 2;
				}
				break;

			// Once `stage` reaches 2, the tableux is ready.
			// Move on to the next part of the program.
			default:
				return 0;
		}

		update_cursor(cursor_x, cursor_y, tab);
	}

	return 0;
}


int solve_stage(Tableux *tab) {
	BigM **data = extract_grid(tab);
	char **row_names = extract_row_names(tab);
	char **column_names = extract_column_names(tab);

	Matrix *mat = new_matrix_with_data(tab->rows-1, tab->columns-1, data);

	*mat = simplex(*mat, row_names, column_names);

	tab = matrix_into_tableux(mat, row_names, tab);


	return 0;
}


int main() {
	dclear(0xffff);

	Tableux *tab = tableux_construction_stage();

	tableux_input_stage(tab);
	solve_stage(tab);
	dclear(0xFFFF);
	display_tableux(tab);
	dupdate();

	free_tableux(tab);

	while (true) {
		getkey();
	}

	return 0;
}

