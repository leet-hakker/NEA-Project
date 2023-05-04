#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "../../include/bigm.h"
#include "../../include/fraction.h"
#include "../../include/matrix.h"

// Returns `true` if the given matrix is
// optimal, meaning that there are no
// negative values in the objective row
// (except for the value column)
bool isoptimal(Matrix *matrix) {
    BigM minimum = get(matrix, matrix->rows-1, 0);
    BigM value;

    for (int i = 0; i < matrix->columns-1; i++) {
        value = get(matrix, matrix->rows-1, i);
        if (BigM_lt(&value, &minimum)) { 
            minimum = value;
        }
    }

    BigM zero = BigM_zero();

    return BigM_ge(&minimum, &zero);
}

// Returns the index of the most negative
// entry in the objective row, except the
// value column.
int pivot_column(Matrix *matrix) {
    BigM minimum = get(matrix, matrix->rows-1, 0);
    int index = 0;
    BigM value;

    for (int i = 0; i < matrix->columns-1; i++) {
        value = get(matrix, matrix->rows-1, i);
        if (BigM_lt(&value, &minimum)) { 
            minimum = value;
            index = i;
        }
    }

    return index;
}

// Returns the pivot row, based on theta values.
int pivot_row(Matrix *matrix, int *pivt_col) {
    BigM theta = new_BigM(fraction_zero(), new_fraction(1, 1));
    BigM minimum = theta;
    int index = 0;
    BigM value;
    BigM zero = BigM_zero();

    for (int row = 0; row < matrix->rows-1; row++) {
        value = get(matrix, row, *pivt_col);

        // If value is 0, division by it will cause an error. We want to avoid this case.
        // We know that as values approach 0, the result of dividing by this value increases.
        // Thus for this case we assume that dividing by zero will result in an infinitely large
        // value. We want to select the smallest theta value, so we can immediately ignore
        // any values of 0.
        if (BigM_eq(value, BigM_zero())) continue;
        theta = div_BigM(get(matrix, row, matrix->columns-1), value);
        if (BigM_ge(&theta, &zero) && BigM_lt(&theta, &minimum)) {
            minimum = theta;
            index = row;
        }
    }

    return index;
}

// Solves the given matrix using the simplex algorithm and returns it
// to the user.
Matrix simplex(Matrix matrix, char** row_names, char** column_names) {
    int column, row;

    // This loop will iterate until the matrix is optimal.
    while (!isoptimal(&matrix)) {
        // Finding the pivot cell, and fetching its value.
        column = pivot_column(&matrix);
        row = pivot_row(&matrix, &column);
        BigM pivot_value = get(&matrix, row, column);

        // Divide pivot row by pivot cell value
        for (int i = 0; i < matrix.columns; i++) {
            BigM current_column_value = get(&matrix, row, i);
            set(&matrix, row, i, div_BigM(current_column_value, pivot_value));
        }

        // Set the row title of the pivot row to the column title of
        // the pivot column
        row_names[row] = strdup(column_names[column]);

        for (int i = 0; i < matrix.rows; i++) {
            // Don't modify the pivot row, so continue
            if (i == row) continue;
            BigM current_row_pivot_column_value = get(&matrix, i, column);

            // Subtract the value in the cell at the pivot column in the current row,
            // multiplied by the value in the cell at the pivot row in the current column,
            // from the current cell.
            for (int j = 0; j < matrix.columns; j++) {
                BigM pivot_row_value = get(&matrix, row, j);
                BigM current_cell_value = get(&matrix, i, j);
                set(&matrix, i, j, sub_BigM(current_cell_value, mul_BigM(current_row_pivot_column_value, pivot_row_value)));
            }
        }
    }

    return matrix;
}