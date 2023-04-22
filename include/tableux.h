#ifndef TABLEUX_H
#define TABLEUX_H
#include <stdlib.h>
#include <stdbool.h>
#include "visualcell.h"
#include "bigm.h"
#include "matrix.h"

extern const uint8_t MAXROWS;
extern const uint8_t MAXCOLS;
extern const uint8_t MINROWS;
extern const uint8_t MINCOLS;

typedef struct Tableux {
    uint8_t rows;
    uint8_t columns;
    uint8_t cursor_x;
    uint8_t cursor_y;
    VisualCell ***grid;
} Tableux;

Tableux *new_tableux(int rows, int columns);
void free_tableux(Tableux *tab);
void display_tableux(Tableux *tab);
void update_cursor(uint8_t cursor_x, uint8_t cursor_y, Tableux *tab);
char **extract_row_names(Tableux *tab);
char **extract_column_names(Tableux *tab);
BigM **extract_grid(Tableux *tab);
Tableux *matrix_into_tableux(Matrix *mat, char **row_names, Tableux *tab);

#endif