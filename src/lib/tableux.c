#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#ifndef FXCG50
#define FXCG50
#endif
#include "../../include/visualcell.h"
#include "../../include/fraction.h"
#include "../../include/bigm.h"
#include "../../include/matrix.h"
#include "../../include/input_validation.h"

const uint16_t ROWCOLBGCOLOUR = 0xdefb;
const uint8_t MAXROWS = 5;
const uint8_t MAXCOLS = 10;
const uint8_t MINROWS = 4;
const uint8_t MINCOLS = 5;

typedef struct Tableux {
    uint8_t rows;
    uint8_t columns;
    uint8_t cursor_x;
    uint8_t cursor_y;
    VisualCell ***grid;
} Tableux;

// Returns a new tableux with the given dimensions.
Tableux *new_tableux(uint8_t rows, uint8_t columns) {
    Tableux *tab = malloc(sizeof(Tableux));
    tab->rows = rows;
    tab->columns = columns;

    // To ensure that we fill the screen.
    unsigned int cellwidth = 394 / columns;
    unsigned int cellheight = cellwidth / CELL_W_TO_H_RATIO; 

    // Using calloc to allow us to not set some values.
    tab->grid = calloc(rows, sizeof(VisualCell**));
    for (int i = 0; i < rows; i++) {
        tab->grid[i] = calloc(columns+1, sizeof(VisualCell*));
    }

    // Assigning each member of the grid its own cell.
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            tab->grid[i][j] = new_viscell(j*cellwidth, i*cellheight, cellwidth, cellheight, false, "");
        }
    }

    // Setting the first row and column to have a different background colour.
    for (int i=0; i < rows; i++) {
        tab->grid[i][0]->bgcol = ROWCOLBGCOLOUR;
        tab->grid[i][0]->editable = true;
    }

    for (int i=0; i < columns; i++) {
        tab->grid[0][i]->bgcol = ROWCOLBGCOLOUR;
        tab->grid[0][i]->editable = true;
    }

    // Setting the cursor
    tab->cursor_x = 1;
    tab->cursor_y = 0;

    tab->grid[tab->cursor_y][tab->cursor_x]->selected = true;

    // Important cell values that wont change
    tab->grid[0][0]->contents = "B.v.";
    tab->grid[0][columns-1]->contents = "Value";
    tab->grid[0][0]->editable = false;
    tab->grid[0][columns-1]->editable = false;

    return tab;
}

// Frees the given tableux,
// and every cell it contains
void free_tableux(Tableux *tab) {
    if (tab == NULL) {
        return;
    }
    for (int i=0; i < tab->rows; i++) {
        for (int j=0; j < tab->columns; j++) {
            if (tab->grid[i] != NULL && tab->grid[i][j] != NULL) {
                free_viscell(tab->grid[i][j]);
            }
        }
        free(tab->grid[i]);
    }
    free(tab->grid);
    free(tab);
}

// Draws the tableux by drawing every
// cell it contains
void display_tableux(Tableux *tab) {
    for (int i=0; i < tab->rows; i++) {
        for (int j=0; j < tab->columns; j++) {
            draw_cell(tab->grid[i][j]);
        }
    }
}

// Updates the tableux to reflect the current
// location of the cursor
void update_cursor(uint8_t cursor_x, uint8_t cursor_y, Tableux *tab) {
    tab->grid[tab->cursor_y][tab->cursor_x]->selected = false;
    tab->grid[cursor_y][cursor_x]->selected = true;
    tab->cursor_x = cursor_x;
    tab->cursor_y = cursor_y;
}

// Returns an array that contains the row names
// of the tableux, in order.
char **extract_row_names(Tableux *tab) {
    char **row_names = calloc(tab->rows-1, sizeof(char*));
    for (int i=1; i < tab->rows-1; i++) {
        row_names[i-1] = malloc(25);
        strcpy(row_names[i-1], tab->grid[i][0]->contents);
    }

    return row_names;
}

// Returns an array that contains the column names
// of the tableux, in order.
char **extract_column_names(Tableux *tab) {
    char **column_names = calloc(tab->columns-1, sizeof(char*));
    for (int i=1; i < tab->columns-1; i++) {
        column_names[i-1] = malloc(25);
        strcpy(column_names[i-1], tab->grid[0][i]->contents);
    }
    
    return column_names;
}

// Returns a 2D array that contains the values
// of the tableux
BigM **extract_grid(Tableux *tab) {
    BigM **grid = calloc(tab->rows-1, sizeof(BigM*));
    for (int i=0; i < tab->rows-1; i++) {
        grid[i] = calloc(tab->columns-1, sizeof(BigM));
    }

    for (int i=0; i < tab->rows-1; i++) {
        for (int j=0; j < tab->columns-1; j++) {
            grid[i][j] = string_to_bigm(tab->grid[i+1][j+1]->contents);
        }
    }

    return grid;
}

// Inserts the data inside the matrix into the tableux,
// by converting each entry into its string representation
Tableux *matrix_into_tableux(Matrix *mat, char **row_names, Tableux *tab) {
    // Set row titles
    for (int i=1; i < mat->rows; i++) {
        tab->grid[i][0]->contents = row_names[i-1];
    }

    // Insert matrix data as strings
    char *str = malloc(25 * sizeof(char));
    for (int i=0; i < mat->rows; i++) {
        for (int j=0; j < mat->columns; j++) {
            tab->grid[i+1][j+1]->contents = strdup(BigM_str(get(mat, i, j), str));
        }
    }

    return tab;
}