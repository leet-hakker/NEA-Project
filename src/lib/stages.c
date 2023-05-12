#include "../../include/tableux.h"
#ifndef FXCG50
#define FXCG50
#endif
#include <gint/display.h>
#include <gint/keyboard.h>
#include <stdint.h>
#include <string.h>

// Checks that every row and column
// title is filled in, return true
// if it is.
bool check_stage_0(Tableux *tab) {
    char *empty = calloc(1, 1);
    for (int i=0; i < tab->columns; i++) {
        if (tab->grid[0][i]->contents[0] == empty[0]) {
            free(empty);
            return false;
        }
    }

    for (int i=0; i < tab->rows; i++) {
        if (tab->grid[i][0]->contents[0] == empty[0]) {
            free(empty);
            return false;
        }
    }

    free(empty);

    return true;
}

// Returns true if every cell in the grid has been
// filled with data.
bool check_stage_1(Tableux *tab) {
    char *empty = calloc(1, 1);
    for (int i=1; i < tab->rows; i++) {
        for (int j=1; j < tab->columns; j++) {
            if (tab->grid[i][j]->contents[0] == empty[0]) {
                free(empty);
                return false;
            }
        }
    }

    free(empty);

    return true;

}
