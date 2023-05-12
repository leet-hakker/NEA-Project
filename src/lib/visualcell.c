#ifndef FXCG50
#define FXCG50
#endif
#include <gint/display.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

const int BORDERPX = 1;
const int CELL_W_TO_H_RATIO = 2;

typedef struct VisualCell {
    int x;
    int y;
    int x_dim;
    int y_dim;
    bool selected;
    bool editable;
    uint16_t bgcol;
    char *contents;
} VisualCell;

// Returns a new VisualCell with the values provided, setting suitable defaults.
VisualCell *new_viscell(int x, int y, int x_dim, int y_dim, bool selected, char *contents) {
    VisualCell *cell = malloc(sizeof(VisualCell));

    cell->x = x;
    cell->y = y;
    cell->x_dim = x_dim;
    cell->y_dim = y_dim;
    cell->selected = selected;
    cell->editable = false;
    cell->bgcol = 0xffff;
    cell->contents = (char*)calloc(20, sizeof(char));
    strcpy(cell->contents, contents);

    return cell;
}

// Frees the given cell
void free_viscell(VisualCell *cell) {
    free(cell->contents);
    free(cell);
}

// Draws the contents of the cell, at the
// position of the cell
void draw_cell_contents(VisualCell *cell) {
    const font_t *font = dfont_default();

    dtext(cell->x+BORDERPX+1, cell->y + cell->y_dim - font->line_height - 3, 0x0000, cell->contents);
}

// Draws the given cell
// Will be drawn with a thicker border
// if the cell is selected currently
void draw_cell(VisualCell *cell) {
    drect_border(cell->x, 
                cell->y,
                cell->x + cell->x_dim, 
                cell->y + cell->y_dim, 
                cell->bgcol, 
                BORDERPX+2*(cell->selected), 
                0x0000
                );

    draw_cell_contents(cell);
    
}