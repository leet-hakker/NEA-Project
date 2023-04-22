#ifndef INPUT_H
#define INPUT_H
#include <gint/keyboard.h>

bool process_key_construction_stage(key_event_t key, VisualCell *row_number_cell, VisualCell *column_number_cell);
bool process_key_rowcol_stage(key_event_t key, uint8_t *cursor_x, uint8_t *cursor_y, Tableux *tab);
bool process_key_tableux_stage(key_event_t key, uint8_t *cursor_x, uint8_t *cursor_y, Tableux *tab);
#endif