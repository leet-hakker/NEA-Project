#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/bigm.h"


typedef struct Matrix {
    int rows;
    int columns;
    BigM **values;
} Matrix;

// Frees the data contained in the matrix,
// and then frees the matrix
void free_matrix(Matrix *mat) {
    for (int i=0; i < mat->rows; i++) {
        free(mat->values[i]);
    }
    free(mat->values);

    free(mat);
}

// Returns an empty matrix with the dimensions
// given
Matrix* new_matrix(int rows, int columns) {
    Matrix* mat = malloc(sizeof(Matrix));
    if (mat == NULL) {
        return NULL;
    }
    mat->rows = rows;
    mat->columns = columns;
    mat->values = malloc(sizeof(BigM**) * rows);
    if (mat->values == NULL) {
        free(mat);
        return NULL;
    }
    for (int i = 0; i < rows; i++) {
        mat->values[i] = malloc(sizeof(BigM) * columns);
        if (mat->values[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(mat->values[j]);
            }
            free(mat->values);
            free(mat);
            return NULL;
        }
    }
    return mat;
}

// Returns a new matrix of dimensions rows x columns, with the data
// provided inserted in.
Matrix* new_matrix_with_data(int rows, int columns, BigM** data) {
    Matrix* mat = new_matrix(rows, columns);
    if (mat == NULL) {
        return NULL;
    }
    for (int i = 0; i < rows; i++) {
        memcpy(mat->values[i], data[i], sizeof(BigM) * columns);
    }
    return mat;
}

// Returns the value contained in the matrix at the
// given point
BigM get(const Matrix* mat, int row, int column) {
    return mat->values[row][column];
}

// Sets the cell at row, column to the value given.
bool set(Matrix* mat, int row, int column, BigM value) {
    if (row > mat->rows-1) { 
        return false;
    } else if (column > mat->columns-1) {
        return false;
    }
    mat->values[row][column] = value;
    return true;
}