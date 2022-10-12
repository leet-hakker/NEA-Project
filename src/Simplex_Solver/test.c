#include <stdio.h>
#include "fraction.h"

int main() {
  Fraction frac1 = Fraction_new(2, 1);
  Fraction frac2 = Fraction_new(3, 1);

  Fraction div_frac = Fraction_div(frac1, frac2);

  char* str = Fraction_str(div_frac);
  printf("%s", str);
}
