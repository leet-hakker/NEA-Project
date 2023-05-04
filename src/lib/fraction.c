#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

// Returns the Greatest Common Divisor
// between the two given integers.
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

// Simplifies the given fraction by dividing both the numerator
// and the denominator by their gcd.
Fraction simplify_fraction(Fraction* frac) {
    int divisor = gcd(abs(frac->numerator), abs(frac->denominator));
    frac->numerator /= divisor;
    frac->denominator /= divisor;
    return *frac;
}


// Returns a new fraction, with the given `numerator and 
// `denominator`
Fraction new_fraction(int numerator, int denominator) {
    Fraction *result_ptr = malloc(sizeof(Fraction));

    // If the pointer received from malloc is NULL,
    // exit. Something has gone terribly wrong.
    assert(result_ptr != NULL);
    result_ptr->numerator = numerator;
    result_ptr->denominator = denominator;

    // Simplify the fraction, to minimise complexity.
    Fraction result = simplify_fraction(result_ptr);
    free(result_ptr);
    return result;
}

// Returns the string that represents the given `fraction`,
// inserting it into the given `str`
char *fraction_str(Fraction frac, char *str) {
    // If the denominator is one, the fraction is an integer,
    // if the numerator is 0, regardless of denominator, it is
    // 0, so just return the numerator as a string.
    if (frac.denominator == 1 || frac.numerator == 0) {
        sprintf(str, "%d", frac.numerator);
        return str;
    } else {
        sprintf(str, "%d/%d", frac.numerator, frac.denominator);
        return str;
    }
}

// Returns the fractions representation of zero. Useful for comparisons.
Fraction fraction_zero() {
    return (Fraction) {0, 1};
}

// Returns true if the given fraction is equal to zero.
bool fraction_is_zero(Fraction frac) {
    return frac.numerator == 0;
}

// Modifies the given fractions to ensure that they have the
// same denominator.
void make_common_denominator(Fraction* frac1, Fraction* frac2) {
    frac1->numerator *= frac2->denominator;
    frac1->denominator *= frac2->denominator;
    frac2->numerator *= frac1->denominator / frac2->denominator;
    frac2->denominator = frac1->denominator;
    
    assert(frac1->denominator == frac2->denominator);
}

// Returns the absolute value of the given fraction.
Fraction abs_fraction(Fraction frac) {
    frac.numerator = abs(frac.numerator);
    frac.denominator = abs(frac.denominator);
    return simplify_fraction(&frac);
}

// Returns true if the two fractions are equal.
bool fraction_eq(Fraction frac1, Fraction frac2) {
    make_common_denominator(&frac1, &frac2);
    return frac1.numerator == frac2.numerator;
}

// Returns true if the two fractions are not equal
bool fraction_ne(Fraction frac1, Fraction frac2) {
    make_common_denominator(&frac1, &frac2);
    return frac1.numerator != frac2.numerator;
}

// Returns true if frac1 is less than frac2
bool fraction_lt(Fraction frac1, Fraction frac2) {
    make_common_denominator(&frac1, &frac2);
    return frac1.numerator < frac2.numerator;
}

// Returns true if frac1 is less than or equal to
// frac2
bool fraction_lte(Fraction frac1, Fraction frac2) {
    make_common_denominator(&frac1, &frac2);
    return frac1.numerator <= frac2.numerator;
}

// Returns true if frac1 is greater than frac2
bool fraction_gt(Fraction frac1, Fraction frac2) {
    make_common_denominator(&frac1, &frac2);
    return frac1.numerator > frac2.numerator;
}

// Returns true if frac1 is greater than or equal to
// frac2
bool fraction_gte(Fraction frac1, Fraction frac2) {
    make_common_denominator(&frac1, &frac2);
    return frac1.numerator >= frac2.numerator;
}

// Returns the sum of the two fractions given.
Fraction fraction_add(Fraction frac1, Fraction frac2) {
    Fraction temp1 = frac1;
    Fraction temp2 = frac2;

    // Make the denominators of the two fractions the same
    make_common_denominator(&temp1, &temp2);

    // If the denominators are not the same, something has gone
    // wrong. Exit immediately.
    assert(temp1.denominator == temp2.denominator);
    return simplify_fraction(&(Fraction) {temp1.numerator + temp2.numerator, temp1.denominator});
}


// Returns frac1 - frac2.
Fraction fraction_subtract(Fraction frac1, Fraction frac2) {
    Fraction temp1 = frac1;
    Fraction temp2 = frac2;
    make_common_denominator(&temp1, &temp2);
    assert(temp1.denominator == temp2.denominator);
    return simplify_fraction(&(Fraction) {temp1.numerator - temp2.numerator, temp1.denominator});
}

// Returns the product of the two fractions.
Fraction fraction_multiply(Fraction frac1, Fraction frac2) {
    return simplify_fraction(&(Fraction) {frac1.numerator * frac2.numerator, frac1.denominator * frac2.denominator});
}

// Returns frac1 / frac2
Fraction fraction_divide(Fraction frac1, Fraction frac2) {
    if (frac1.denominator * frac2.numerator < 0) {
        return simplify_fraction(&(Fraction) {-frac1.numerator * frac2.denominator, frac1.denominator * frac2.numerator});
    }
    return simplify_fraction(&(Fraction) {frac1.numerator * frac2.denominator, frac2.numerator * frac1.denominator});
}
