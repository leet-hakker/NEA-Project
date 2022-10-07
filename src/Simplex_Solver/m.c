#include <stdio.h>
#include <math.h>
#include "fraction.c"

typedef struct {
 Fraction num_val;
 Fraction m_val;
} M;


M M_new(Fraction num_val, Fraction m_val) {
  M new_m;

  new_m.num_val = num_val;
  new_m.m_val = m_val;

  return new_m;
}

int main() {
  M my_m = M_new(Fraction_new(0, 1), Fraction_new(1, 2));

  printf("%s", Fraction_str(my_m.num_val));
  printf("\n");
  printf("%f", 1.0f/2.0f);

  return 0;
}
