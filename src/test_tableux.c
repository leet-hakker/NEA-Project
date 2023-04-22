#include "../include/fraction.h"
#include "../include/bigm.h"
#include "../include/matrix.h"
#include "../include/tableux.h"
#include "../include/simplex.h"

int main() {
    Tableux *tab = new_tableux(4, 6);
    
    char *data[4][6] = {
                        {"B.v.", "X", "Y", "R", "S", "Value"},
                        {"R", "5", "7", "1", "0", "70"},
                        {"S", "10", "3", "0", "1", "60"},
                        {"P", "-3", "-2", "0", "0", "0"}
                    };

    for (int i=0; i < 4; i++) {
        for (int j=0; j < 6; j++) {
            tab->grid[i][j]->contents = data[i][j];
        }
    }

    char **rows = extract_row_names(tab);
    char **cols = extract_column_names(tab);
    BigM **grid = extract_grid(tab);

    Matrix *mat = new_matrix_with_data(3, 5, grid);

    print_mat(mat);

    *mat = simplex(*mat, rows, cols);

    print_mat(mat);

    tab = matrix_into_tableux(mat, rows, tab);

    grid = extract_grid(tab);

    mat = new_matrix_with_data(3, 5, grid);

    print_mat(mat);

}