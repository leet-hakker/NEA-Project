#include <stdio.h>
#include <math.h>
#include "fraction.h"

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

