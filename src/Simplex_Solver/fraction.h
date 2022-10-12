#ifndef _FRACTION_H
#define _FRACTION_H
typedef struct {
  int numerator;
  int denominator;
} Fraction;
Fraction Fraction_new(int numerator, int denominator);
Fraction Fraction_new_from_float(float number);
Fraction Fraction_neg(Fraction frac);
Fraction Fraction_simplify(Fraction frac);
Fraction Fraction_add(Fraction frac1, Fraction frac2);
Fraction Fraction_sub(Fraction frac1, Fraction frac2);
Fraction Fraction_mul(Fraction frac1, Fraction frac2);
Fraction Fraction_div(Fraction frac1, Fraction frac2);
char* Fraction_str(Fraction frac);
#endif
