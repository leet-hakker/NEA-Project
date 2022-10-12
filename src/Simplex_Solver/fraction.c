#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"

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



Fraction Fraction_simplify(Fraction frac) {
  int neg = 1;

  // If only one of the parts is negative, the whole fraction is.
  // preserve this information
  if ((frac.numerator < 0) ^ (frac.denominator < 0)) {
    neg = -1;
  }

  // Common denominator of numerator and denominator
  int common_denom = gcd(frac.numerator, frac.denominator);

  // Return a new fraction with the appropriate sign, simplified by dividing by GCD
  return Fraction_new(abs(frac.numerator) / common_denom * neg, abs(frac.denominator) / common_denom);
}

// We may need to convert from a float to a fraction type
// so this function is required.
// It multiplies by 10 until the least significant digit
// is >= 1.
// Then as the denominator, the power of 10 that the float
// was multiplied by. Putting this fraction through the simplify
// function generates a simplified fraction for the float.
Fraction Fraction_new_from_float(float number) {
  int count = 0;
  while (ceil(number) !=number) {
    number *= 10;
    if (count) {
      count *= 10;
    } else {
      count++;
    }
  }

  return Fraction_simplify(Fraction_new(number, count));

}
Fraction Fraction_neg(Fraction frac) {
  frac.numerator = -frac.numerator;

  return frac;
}

Fraction Fraction_add(Fraction frac1, Fraction frac2) {
  if (frac1.denominator == frac2.denominator) {
    return Fraction_new(frac1.numerator + frac2.numerator, frac1.denominator);
  }

  Fraction new_frac;
  new_frac.denominator = frac1.numerator * frac2.numerator;
  frac1.numerator *= frac2.denominator;
  frac2.numerator *= frac1.denominator;
  new_frac.numerator = frac1.numerator + frac2.numerator;

  return Fraction_simplify(new_frac);
}

Fraction Fraction_mul(Fraction frac1, Fraction frac2) {
  Fraction new_frac;

  new_frac.numerator = frac1.numerator * frac2.numerator;
  new_frac.denominator = frac1.denominator * frac2.denominator;

  return Fraction_simplify(new_frac);
}

Fraction Fraction_sub(Fraction frac1, Fraction frac2) {
  return Fraction_add(frac1, Fraction_neg(frac2));
}

Fraction Fraction_div(Fraction frac1, Fraction frac2) {
  swap(&frac2.numerator, &frac2.denominator);

  return Fraction_mul(frac1, frac2);
}

char* Fraction_str(Fraction frac) {
  static char str[21];

  sprintf(str, "%d/%d", frac.numerator, frac.denominator);

  return str;
}
