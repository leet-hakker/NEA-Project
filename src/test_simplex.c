#include "../include/fraction.h"
#include "../include/bigm.h"
#include "../include/matrix.h"
#include "../include/simplex.h"
#include <assert.h>

int main() {
    BigM data1[3][5] = { {new_BigM(new_fraction(5, 1), fraction_zero()), new_BigM(new_fraction(7, 1), fraction_zero()), new_BigM(new_fraction(1, 1), fraction_zero()), new_BigM(fraction_zero(), fraction_zero()), new_BigM(new_fraction(70, 1), fraction_zero())},
    {new_BigM(new_fraction(10, 1), fraction_zero()), new_BigM(new_fraction(3, 1), fraction_zero()), new_BigM(fraction_zero(), fraction_zero()), new_BigM(new_fraction(1, 1), fraction_zero()), new_BigM(new_fraction(60, 1), fraction_zero())},
    {new_BigM(new_fraction(-3, 1), fraction_zero()), new_BigM(new_fraction(-2, 1), fraction_zero()), new_BigM(fraction_zero(), fraction_zero()), new_BigM(fraction_zero(), fraction_zero()), new_BigM(fraction_zero(), fraction_zero())}};

    //  5 7 1 0 70
    //  10 3 0 1 60
    // -3 -2 0 0 0

    BigM **dat = malloc(3*sizeof(BigM*));
    for (int i=0; i < 3; i++) {
        dat[i] = malloc(5*sizeof(BigM));
        for (int j=0; j < 5; j++) {
            dat[i][j] = data1[i][j];
        }
    }

    BigM solution1[3][5] = {{new_BigM(new_fraction(0, 1), fraction_zero()), new_BigM(new_fraction(1, 1), fraction_zero()), new_BigM(new_fraction(2, 11), fraction_zero()), new_BigM(new_fraction(-1, 11), fraction_zero()), new_BigM(new_fraction(80, 11), fraction_zero())},
    {new_BigM(new_fraction(1, 1), fraction_zero()), new_BigM(fraction_zero(), fraction_zero()), new_BigM(new_fraction(-3, 55), fraction_zero()), new_BigM(new_fraction(7, 55), fraction_zero()), new_BigM(new_fraction(42, 11), fraction_zero())},
    {new_BigM(fraction_zero(), fraction_zero()), new_BigM(fraction_zero(), fraction_zero()), new_BigM(new_fraction(1, 5), fraction_zero()), new_BigM(new_fraction(1, 5), fraction_zero()), new_BigM(new_fraction(26, 1), fraction_zero())}
    };

    char *columns1[5] = {"x", "y", "r", "s", "Value"};
    char *rows1[3] = {"r", "s", "P"};
    char *row_ans1[3] = {"y", "x", "P"};

    Matrix *mat = new_matrix_with_data(3, 5, dat);

    Matrix sol = simplex(*mat, rows1, columns1);

    for (int i=0; i < 3; i++) {
        for (int j=0; j < 5; j++) {
            assert(BigM_eq(get(&sol, i, j), solution1[i][j]));
        }
    }

    print_mat(&sol);

    printf("%s, %s, %s\n", rows1[0], rows1[1], rows1[2]);

    free_matrix(mat);
    for (int i=0; i < sol.rows; i++) {
        free(dat[i]);
    }
    free(rows1[0]);
    free(rows1[1]);
    free(dat);
}