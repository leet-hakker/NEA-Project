#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

int gcd(int a, int b) {
    if (b == 0) {
        return abs(a);
    }
    return gcd(b, a % b);
}

typedef struct {
    int numerator;
    int denominator;
} Fraction;

Fraction simplify_fraction(Fraction* frac) {
    int divisor = gcd(abs(frac->numerator), abs(frac->denominator));
    frac->numerator /= divisor;
    frac->denominator /= divisor;
    return *frac;
}

Fraction new_fraction(int numerator, int denominator) {
    Fraction *result_ptr = malloc(sizeof(Fraction));
    assert(result_ptr != NULL);
    result_ptr->numerator = numerator;
    result_ptr->denominator = denominator;
    Fraction result = simplify_fraction(result_ptr);
    free(result_ptr);
    return result;
}


char *fraction_str(Fraction frac, char *str) {
    if (frac.denominator == 1 || frac.numerator == 0) {
        sprintf(str, "%d", frac.numerator);
        return str;
    } else {
        sprintf(str, "%d/%d", frac.numerator, frac.denominator);
        return str;
    }
}

Fraction fraction_zero() {
    return (Fraction) {0, 1};
}

bool fraction_is_zero(Fraction frac) {
    return frac.numerator == 0;
}

void make_common_denominator(Fraction* frac1, Fraction* frac2) {
    frac1->numerator *= frac2->denominator;
    frac1->denominator *= frac2->denominator;
    frac2->numerator *= frac1->denominator / frac2->denominator;
    frac2->denominator = frac1->denominator;
    
    assert(frac1->denominator == frac2->denominator);
}

Fraction abs_fraction(Fraction frac) {
    frac.numerator = abs(frac.numerator);
    frac.denominator = abs(frac.denominator);
    return simplify_fraction(&frac);
}

bool fraction_eq(Fraction frac1, Fraction frac2) {
    make_common_denominator(&frac1, &frac2);
    return frac1.numerator == frac2.numerator;
}

bool fraction_ne(Fraction frac1, Fraction frac2) {
    make_common_denominator(&frac1, &frac2);
    return frac1.numerator != frac2.numerator;
}

bool fraction_lt(Fraction frac1, Fraction frac2) {
    make_common_denominator(&frac1, &frac2);
    return frac1.numerator < frac2.numerator;
}

bool fraction_lte(Fraction frac1, Fraction frac2) {
    make_common_denominator(&frac1, &frac2);
    return frac1.numerator <= frac2.numerator;
}

bool fraction_gt(Fraction frac1, Fraction frac2) {
    make_common_denominator(&frac1, &frac2);
    return frac1.numerator > frac2.numerator;
}

bool fraction_gte(Fraction frac1, Fraction frac2) {
    make_common_denominator(&frac1, &frac2);
    return frac1.numerator >= frac2.numerator;
}

Fraction fraction_add(Fraction frac1, Fraction frac2) {
    Fraction temp1 = frac1;
    Fraction temp2 = frac2;
    make_common_denominator(&temp1, &temp2);
    assert(temp1.denominator == temp2.denominator);
    return simplify_fraction(&(Fraction) {temp1.numerator + temp2.numerator, temp1.denominator});
}

Fraction fraction_subtract(Fraction frac1, Fraction frac2) {
    Fraction temp1 = frac1;
    Fraction temp2 = frac2;
    make_common_denominator(&temp1, &temp2);
    assert(temp1.denominator == temp2.denominator);
    return simplify_fraction(&(Fraction) {temp1.numerator - temp2.numerator, temp1.denominator});
}

Fraction fraction_multiply(Fraction frac1, Fraction frac2) {
    return simplify_fraction(&(Fraction) {frac1.numerator * frac2.numerator, frac1.denominator * frac2.denominator});
}

Fraction fraction_divide(Fraction frac1, Fraction frac2) {
    if (frac1.denominator * frac2.numerator < 0) {
        return simplify_fraction(&(Fraction) {-frac1.numerator * frac2.denominator, frac1.denominator * frac2.numerator});
    }
    return simplify_fraction(&(Fraction) {frac1.numerator * frac2.denominator, frac2.numerator * frac1.denominator});
}
