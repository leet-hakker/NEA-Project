#ifndef SIMPLEX_H
#define SIMPLEX_H

#include "bigm.h"
#include "matrix.h"

bool isoptimal(Matrix *matrix);
int pivot_column(Matrix *matrix);
int pivot_row(Matrix *matrix, int *pivt_col);
Matrix simplex(Matrix matrix, char** row_names, char** column_names);

#endif // SIMPLEX_H