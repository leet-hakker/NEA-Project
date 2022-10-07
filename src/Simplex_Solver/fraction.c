#include <stdio.h>
typedef struct {
  int numerator;
  int denominator;
} Fraction;

Fraction Fraction_new(int numerator, int denominator) {
  Fraction new_frac;

  new_frac.numerator = numerator;
  new_frac.denominator = denominator;

  return new_frac;
}

char * Fraction_str(Fraction frac) {
  char str[21];

  snprintf(str, "%d", frac.numerator);

  printf("%s", str);

  return str;
}
