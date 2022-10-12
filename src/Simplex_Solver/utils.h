void swap (int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


int min(int num1, int num2) {
    return (num1 > num2 ) ? num2 : num1;
}

int trailing_zeros(unsigned int num) {
    int count = 0;
 
    while (num != 0)
    {
        if ((num & 1) == 1)
        {
            break;
        }
        else
        {
            count++;
            num = num >> 1;

        }
    }
    return count;
}

int gcd(int u, int v) {
    u = abs(u);
    v = abs(v);


  // Base cases: gcd(n, 0) = gcd(0, n) = n
  if (u == 0) {
      return v;
  } else if (v == 0) {
      return u;
  }

  // Using identities 2 and 3:
  // gcd(2ⁱ u, 2ʲ v) = 2ᵏ gcd(u, v) with u, v odd and k = min(i, j)
  // 2ᵏ is the greatest power of two that divides both u and v
  int i = trailing_zeros(u);
  u >>= i;
  int j = trailing_zeros(v);
  v >>= j;
  int  k = min(i, j);

  while (1) {
      // Swap if necessary so u <= v
      if (u > v) {
        swap(&v, &u);
      }
      /// u and v are still both odd after (potentially) swapping

      // Using identity 4 (gcd(u, v) = gcd(|v-u|, min(u, v))
      v -= u;
      /// v is now even, but u is unchanged (and odd)

      // Identity 1: gcd(u, 0) = u
      // The shift by k is necessary to add back the 2ᵏ factor that was removed before the loop
      if (v == 0) {
          return u << k;
      }

      // Identity 3: gcd(u, 2ʲ v) = gcd(u, v) (u is known to be odd)
      v >>= trailing_zeros(v);
      /// v is now odd again
  }
}


