#ifndef FRACTION_H
#define FRACTION_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int gcd(int a, int b);

typedef struct {
    int numerator;
    int denominator;
} Fraction;

Fraction simplify_fraction(Fraction* frac);
Fraction new_fraction(int numerator, int denominator);
char *fraction_str(Fraction frac, char *str);
Fraction fraction_zero();
bool fraction_is_zero(Fraction frac);
void make_common_denominator(Fraction* frac1, Fraction* frac2);
Fraction abs_fraction(Fraction frac);
bool fraction_eq(Fraction frac1, Fraction frac2);
bool fraction_ne(Fraction frac1, Fraction frac2);
bool fraction_lt(Fraction frac1, Fraction frac2);
bool fraction_lte(Fraction frac1, Fraction frac2);
bool fraction_gt(Fraction frac1, Fraction frac2);
bool fraction_gte(Fraction frac1, Fraction frac2);
Fraction fraction_add(Fraction frac1, Fraction frac2);
Fraction fraction_subtract(Fraction frac1, Fraction frac2);
Fraction fraction_multiply(Fraction frac1, Fraction frac2);
Fraction fraction_divide(Fraction frac1, Fraction frac2);

#endif
