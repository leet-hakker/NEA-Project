#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include <stdlib.h>
#include "bigm.h"

typedef struct Matrix {
    int rows;
    int columns;
    BigM** values;
} Matrix;

void free_matrix(Matrix *mat);
Matrix* new_matrix(int rows, int columns);
Matrix* new_matrix_with_data(int rows, int columns, BigM** data);
BigM get(const Matrix* mat, int row, int column);
bool set(Matrix* mat, int row, int column, BigM value);
void print_mat(Matrix *mat);

#endif // MATRIX_H