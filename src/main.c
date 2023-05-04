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

const color_t CHANGED_COLOUR = 0xAAF6;

bool show_options_menu() {
	// A square viscell to represent a checkbox
	// in the centre of the screen
	VisualCell *checkbox = new_viscell(200, 110, 30, 30, true, "");

	bool exit = false;

	while (!exit) {
		dtext(10, 110, 0x0000, "Show steps to solution?");
		draw_cell(checkbox);
		dupdate();
		key_event_t key = getkey();

		// F6, user wants to move on
		if (key.key == KEY_F6) {
			exit = true;
		// EXE toggles the checkbox
		} else if (key.key == KEY_EXE) {
			if (checkbox->bgcol == 0xFFFF) {
				checkbox->bgcol = 0x840F;
			} else {
				checkbox->bgcol = 0xFFFF;
			}
		}
	}

	// If the background colour is 0x840F, then
	// the user wants to show steps.
	return checkbox->bgcol == 0x840F;

}


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

		// Wait for the user to give a key input
		key_event_t key = getkey();

		// Process the key input, if the function
		// returns `true`, exit will be `true` and
		// the loop will terminate
		exit = process_key_construction_stage(key, row_number_cell, column_number_cell);
	}

	// Extracting the desired numbers from the VisCells
	uint8_t row_num = atoi(row_number_cell->contents);
	uint8_t column_num = atoi(column_number_cell->contents);

	free_viscell(row_number_cell);
	free_viscell(column_number_cell);

	dclear(0xFFFF);

	// Create a new tableux with the requested
	// dimensions, and return it.
	Tableux *tab = new_tableux(row_num, column_num);

	return tab;
}

int tableux_input_stage(Tableux *tab) {
	key_event_t key;
	// Set the cursor the the leftmost
	// column title. This is arbitrary.
	uint8_t cursor_x = 1;
	uint8_t cursor_y = 0;
	uint8_t stage = 0;

	while (true) {
		display_tableux(tab);

		dupdate();

		dclear(0xffff);

		key = getkey();

		switch (stage) {
			case 0:
				// If stage=0, then the user still needs to enter the row and
				// column titles into the tableux. This function returns `true`
				// when the user pressed F6 and every title is filled in.
				if (process_key_rowcol_stage(key, &cursor_x, &cursor_y, tab)) {
					stage = 1;
				}
				break;
			
			case 1:
				// At this point the user needs to enter the numbers into the
				// tableux. Again, when the user presses F6 and the grid is
				// filled in, the function here will return true and stage
				// will be set to 2.
				if (process_key_tableux_stage(key, &cursor_x, &cursor_y, tab)) {
					stage = 2;
				}
				break;

			// Once `stage` reaches 2, the tableux is ready.
			// Move on to the next part of the program.
			default:
				return 0;
		}

		// Update the cursor position so that it is
		// shown correctly to the user.
		update_cursor(cursor_x, cursor_y, tab);
	}

	return 0;
}

// This function runs the process of solving the
// tableux received from the user.
int solve_stage(Tableux *tab, bool show_steps) {

	// Extract all the needed information from the 
	// tableux into the parameters the `simplex`
	// functions takes.
	BigM **data = extract_grid(tab);
	char **row_names = extract_row_names(tab);
	char **column_names = extract_column_names(tab);

	// Create a new matrix from the grid that was extracted.
	Matrix *mat = new_matrix_with_data(tab->rows-1, tab->columns-1, data);

	// If the user selected that they wanted to show the steps to
	// the solution, the program will take this branch and they
	// will be highlighted in CHANGED_COLOUR
	if (show_steps) {
		while (!isoptimal(mat)) {
			// Find pivot row and column, then show this
			// to user.
			int pivt_col = pivot_column(mat);
			int pivt_row = pivot_row(mat, &pivt_col);

			// Highlight the pivot cell
			tab->grid[pivt_row+1][pivt_col+1]->bgcol = CHANGED_COLOUR;

			dclear(0xFFFF);
			display_tableux(tab);
			dupdate();

			bool move_on = false;

			// Move on once the user presses F6
			while (!move_on) {
				key_event_t key = getkey();
				move_on = (key.key == KEY_F6);
			}

			
	        BigM pivot_value = get(mat, pivt_row, pivt_col);

			// Divide pivot row by pivot cell value
			for (int i = 0; i < mat->columns; i++) {
				BigM current_column_value = get(mat, pivt_row, i);
				set(mat, pivt_row, i, div_BigM(current_column_value, pivot_value));
			}

			// Insert the matrix back into the tableux, ready
			// to show to the user.
			tab = matrix_into_tableux(mat, row_names, tab);

			// Set the row title.
			strcpy(row_names[pivt_row], column_names[pivt_col]);

			// Set the pivot row's background colour to show
			// that is has been modified
			for (int i=0; i < tab->columns; i++) {
				tab->grid[pivt_row+1][i]->bgcol = CHANGED_COLOUR;
			}


			dclear(0xFFFF);
			display_tableux(tab);
			dupdate();

			// Reset the row title background.
			tab->grid[pivt_row+1][0]->bgcol = ROWCOLBGCOLOUR;

			move_on = false;

			while (!move_on) {
				key_event_t key = getkey();
				move_on = (key.key == KEY_F6);
			}
			
			// Reset background colour for pivot row
			for (int i=1; i < tab->columns; i++) {
				tab->grid[pivt_row+1][i]->bgcol = 0xFFFF;
			}

			// Go through, row by row, column by column, subtracting 
			// value at matrix[row][pivt_col]*matrix[pivt_col][column]
			// from each column

			for (int i=0; i < mat->rows; i++) {
				if (i == pivt_row) continue;

				BigM current_row_pivt_col_value = get(mat, i, pivt_col);

				for (int j=0; j < mat->columns; j++) {
					BigM pivot_row_value = get(mat, pivt_row, j);
					BigM current_cell_value = get(mat, i, j);
					set(mat, i, j, sub_BigM(current_cell_value, mul_BigM(current_row_pivt_col_value, pivot_row_value)));
				}

				tab = matrix_into_tableux(mat, row_names, tab);

				// Set background colour for modified row 
				for (int k=1; k < tab->columns; k++) {
					tab->grid[i+1][k]->bgcol = CHANGED_COLOUR;
				}

				dclear(0xFFFF);
				display_tableux(tab);
				dupdate();

				move_on = false;

				while (!move_on) {
					key_event_t key = getkey();
					move_on = (key.key == KEY_F6);
				}
				
				// Reset background colour for modified row
				for (int k=1; k < tab->columns; k++) {
					tab->grid[i+1][k]->bgcol = 0xFFFF;
				}

			}

		}
	// Otherwise, dump the extracted data directly into
	// `simplex` and solve.
	} else {
		*mat = simplex(*mat, row_names, column_names);
	}

	// Set the tableux, ready to display.
	tab = matrix_into_tableux(mat, row_names, tab);


	return 0;
}


int main() {
	dclear(0xFFFF);

	// Show the user the options menu to start
	bool show_steps = show_options_menu();
	dclear(0xFFFF);

	// Have the user select the Tableux dimensions.
	Tableux *tab = tableux_construction_stage();
	dclear(0xFFFF);

	// Have the user input the data into the Tableux.
	tableux_input_stage(tab);
	dclear(0xFFFF);

	// Solve the Tableux.
	solve_stage(tab, show_steps);
	dclear(0xFFFF);

	// Show the solved Tableux to the user.
	display_tableux(tab);
	dupdate();

	// Free the Tableux, ready to exit.
	free_tableux(tab);

	while (true) {
		getkey();
	}

	return 0;
}

