#include <stdio.h>
#include <stdlib.h>
#include "../../include/tableux.h"
#include "../../include/stages.h"
#include "../../include/input_validation.h"
#ifndef FXCG50
#define FXCG50
#endif
#include <gint/display.h>
#include <gint/keyboard.h>
#include <gint/keycodes.h>


// Processes the given `key` event and moves the cursor if necessary.
bool process_cursor_movement(key_event_t key, uint8_t *cursor_x, uint8_t *cursor_y, Tableux *tab) {
    switch (key.key) {
        // Up
        case KEY_UP:
            if (*cursor_y > 0) {
                *cursor_y -= 1;
            }
            return true;
            break;
        // Down
        case KEY_DOWN:
            if (*cursor_y < tab->rows-1) {
                *cursor_y += 1;
            }
            return true;
            break;
        // Left
        case KEY_LEFT:
            if (*cursor_x > 0) {
                *cursor_x -= 1;
            }
            return true;
            break;
        // Right
        case KEY_RIGHT:
            if (*cursor_x < tab->columns-1) {
                *cursor_x += 1;
            }
            return true;
            break;
        
        default:
            return false;
            break;
    }
}

// Processes common key inputs that are common between most input functions
void process_common_keys(key_event_t key, uint8_t *cursor_x, uint8_t *cursor_y, Tableux *tab) {
    if (key.alpha) {
        if (key.key == KEY_7) {
            if (*cursor_x > 0 && *cursor_y == tab->rows-1) {
                if (strlen(tab->grid[*cursor_y][*cursor_x]->contents) < 20)
                    strncat(tab->grid[*cursor_y][*cursor_x]->contents, "M", 1);
            }
        }
    } else {
        if (key.key == KEY_DEL) {
            const unsigned int length = strlen(tab->grid[*cursor_y][*cursor_x]->contents);
            if (length > 0) 
                tab->grid[*cursor_y][*cursor_x]->contents[length-1] = '\0';
        // If the given key is a number
        } else if (keycode_digit(key.key) > 0) {
            if (strlen(tab->grid[*cursor_y][*cursor_x]->contents) < 20) {
                char digit[2];
                sprintf(digit, "%d", keycode_digit(key.key));
                strncat(tab->grid[*cursor_y][*cursor_x]->contents, digit, 1);
            }
        } else if (key.key == KEY_0) {
            // Work-around because keycode_digit() for some reason does not include 0.
            if (strlen(tab->grid[*cursor_y][*cursor_x]->contents) < 20)
                strncat(tab->grid[*cursor_y][*cursor_x]->contents, "0", 1);
        } else if (key.key == KEY_MINUS) {
            if (strlen(tab->grid[*cursor_y][*cursor_x]->contents) < 20)
                strncat(tab->grid[*cursor_y][*cursor_x]->contents, "-", 1);
        }
    }
}

// Processes key inputs for the tableux construction stage.
// Returns true if the user wants to move on to the next stage.
bool process_key_construction_stage(key_event_t key, VisualCell *row_number_cell, VisualCell *column_number_cell) {
    switch (key.key) {
        case KEY_UP:
            // Increment current cell, if possible
            char *end_ptr;
            long value;
            // If the row number is the cell that is selected,
            // edit that, otherwise, edit the column number.
            if (row_number_cell->selected) {
                value = strtol(row_number_cell->contents, &end_ptr, 10);
                if (value < MAXROWS) {
                    snprintf(row_number_cell->contents, 3, "%ld", value+1);
                }
            } else {
                value = strtol(column_number_cell->contents, &end_ptr, 10);
                if (value < MAXCOLS) {
                    snprintf(column_number_cell->contents, 3, "%ld", value+1);
                }
            }
            return false;
            break;

        case KEY_DOWN:
            // Decrement current cell, if possible
            char *end_ptr_;
            long value_;
            // If the row number is the cell that is selected,
            // edit that, otherwise, edit the column number.
            if (row_number_cell->selected) {
                value_ = strtol(row_number_cell->contents, &end_ptr_, 10);
                if (value_ > MINROWS) {
                    snprintf(row_number_cell->contents, 3, "%ld", value_-1);
                }
            } else {
                value_ = strtol(column_number_cell->contents, &end_ptr_, 10);
                if (value_ > MINCOLS) {
                    snprintf(column_number_cell->contents, 3, "%ld", value_-1);
                }
            }
            return false;
            break;

        case KEY_LEFT:
            // Switch cells.
            row_number_cell->selected = !row_number_cell->selected;
            column_number_cell->selected = !column_number_cell->selected;
            return false;
            break;

        case KEY_RIGHT:
            // Switch cells
            row_number_cell->selected = !row_number_cell->selected;
            column_number_cell->selected = !column_number_cell->selected;
            return false;
            break;
        
        case KEY_F6:
            // User is finished, proceed.
            return true;
            break;

        default:
            break;
    }
}

// Processes key inputs for the row and column name input stage, 
// returns true if the user wants to move on.
bool process_key_rowcol_stage(key_event_t key, uint8_t *cursor_x, uint8_t *cursor_y, Tableux *tab) {
    if (key.key == KEY_F6 && check_stage_0(tab)) {
        // Change the tableux so that it is ready for
        // stage 1.

        for (int i=0; i < tab->columns; i++) {
            tab->grid[0][i]->editable = false;
        }

        for (int i=0; i < tab->rows; i++) {
            tab->grid[i][0]->editable = false;
        }

        for (int i=1; i < tab->rows; i++) {
            for (int j=1; j < tab->columns; j++) {
                tab->grid[i][j]->editable = true;
            }
        }
        return true;
    }


    // Process the keys as though it were to move the cursor,
    // if true, cursor has moved, so return: nothing else
    // to do.
    if (process_cursor_movement(key, cursor_x, cursor_y, tab)) {
        return false;
    }
    // If alpha pressed, process it as a letter
    else if (key.alpha) {
        char *ch;
        switch (key.key) {
            case KEY_XOT:
                ch = "A";
                break;
            
            case KEY_LOG:
                ch = "B";
                break;

            case KEY_LN:
                ch = "C";
                break;
            
            case KEY_SIN:
                ch = "D";
                break;
            
            case KEY_COS:
                ch = "E";
                break;
            
            case KEY_TAN:
                ch = "F";
                break;
            
            case KEY_FRAC:
                ch = "G";
                break;
            
            case KEY_FD:
                ch = "H";
                break;
            
            case KEY_LEFTP:
                ch = "I";
                break;
            
            case KEY_RIGHTP:
                ch = "J";
                break;
            
            case KEY_COMMA:
                ch = "K";
                break;
            
            case KEY_ARROW:
                ch = "L";
                break;
            
            case KEY_7:
                ch = "M";
                break;
            
            case KEY_8:
                ch = "N";
                break;
            
            case KEY_9:
                ch = "O";
                break;
            
            case KEY_4:
                ch = "P";
                break;
            
            case KEY_5:
                ch = "Q";
                break;
            
            case KEY_6:
                ch = "R";
                break;
            
            case KEY_MUL:
                ch = "S";
                break;
            
            case KEY_DIV:
                ch = "T";
                break;
            
            case KEY_1:
                ch = "U";
                break;
            
            case KEY_2:
                ch = "V";
                break;
            
            case KEY_3:
                ch = "W";
                break;
            
            case KEY_ADD:
                ch = "X";
                break;

            case KEY_SUB:
                ch = "Y";
                break;
            
            case KEY_0:
                ch = "Z";
                break;

            default:
                ch = "";
                break;
            }
            char *prev_val = tab->grid[*cursor_y][*cursor_x]->contents;
            sprintf(tab->grid[*cursor_y][*cursor_x]->contents, "%s%s", prev_val, ch);
    // Else, process it as a number
    } else {
        process_common_keys(key, cursor_x, cursor_y, tab);
    }
    return false;
}


// Process keys for the tableux input stage.
// Returns true if the user wants to move on.
bool process_key_tableux_stage(key_event_t key, uint8_t *cursor_x, uint8_t *cursor_y, Tableux *tab) {
    if (key.key == KEY_F6 && check_stage_1(tab)) {
        for (int i=1; i < tab->rows; i++) {
            for (int j=1; j < tab->columns; j++) {
                tab->grid[i][j]->editable = false;
            }
        }
        return true;
    }

    if (tab->grid[*cursor_y][*cursor_x]->editable) {
        // Process input as though it were to move the
        // cursor, if true, cursor has moved: return, 
        // nothing else to do.
        if (process_cursor_movement(key, cursor_x, cursor_y, tab)) {
            return false;
        } else {
            process_common_keys(key, cursor_x, cursor_y, tab);
        }
    }

    return false;
}