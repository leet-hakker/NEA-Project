#ifndef M_H
#define M_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "fraction.h"

typedef struct BigM {
    Fraction num_val;
    Fraction m_val;
} BigM;

BigM new_BigM(Fraction num_val, Fraction m_val);

BigM BigM_zero();

BigM BigM_one();

char *BigM_str(BigM bm, char *str);

BigM add_BigM(BigM bm1, BigM bm2);

BigM sub_BigM(BigM bm1, BigM bm2);

BigM mul_BigM(BigM bm1, BigM bm2);

BigM div_BigM(BigM bm1, BigM bm2);

bool BigM_eq(BigM bm1, BigM bm2);

bool BigM_ne(BigM bm1, BigM bm2);

bool BigM_lt(BigM* a, BigM* b);

bool BigM_le(BigM* a, BigM* b);

bool BigM_gt(BigM* a, BigM* b);

bool BigM_ge(BigM* a, BigM* b);

#endif /* FRACTION_H */