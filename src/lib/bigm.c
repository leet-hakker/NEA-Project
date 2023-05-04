#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../../include/fraction.h"

typedef struct BigM {
    Fraction num_val;
    Fraction m_val;
} BigM;

// Returns a new BigM, with the given num value
// and m value
BigM new_BigM(Fraction num_val, Fraction m_val) {
    BigM bm = {num_val, m_val};
    return bm;
}

// Returns the BigM representation of zero
BigM BigM_zero() {
    return new_BigM(fraction_zero(), fraction_zero());
}

// Returns a string representing the given `bigm`,
// and also places it into `str`
char *BigM_str(BigM bigm, char *str) {
    char num_str[25];
    char m_str[25];
    
    // convert the num_val field to a string
    if (fraction_eq(bigm.num_val, fraction_zero())) {
        sprintf(num_str, "0");
    } else {
        fraction_str(bigm.num_val, num_str);
    }
    
    // convert the m_val field to a string
    if (fraction_eq(bigm.m_val, fraction_zero())) {
        sprintf(m_str, "0");
    } else if (fraction_lt(bigm.m_val, fraction_zero()) && num_str == "0") {
        fraction_str(bigm.m_val, m_str + 1); // add a negative sign manually
        m_str[0] = '-';
    } else {
        fraction_str(bigm.m_val, m_str);
    }

    // combine the two strings into the final BigM string representation
    if (fraction_eq(bigm.num_val, fraction_zero())) {
        if (!fraction_eq(bigm.m_val, fraction_zero())) {
            sprintf(str, "%sM", m_str);
        } else {
            sprintf(str, "0");
        }
    } else if (fraction_eq(bigm.m_val, fraction_zero())) {
        sprintf(str, "%s", num_str);
    } else if (fraction_lt(bigm.m_val, fraction_zero())) {
        sprintf(str, "%s-%sM", num_str, m_str + 1); // add a negative sign manually
    } else {
        sprintf(str, "%s+%sM", num_str, m_str);
    }
    
    return str;
}


// Returns the sum of bm1 and bm2
BigM add_BigM(BigM bm1, BigM bm2) {
    return new_BigM(fraction_add(bm1.num_val, bm2.num_val), fraction_add(bm1.m_val, bm2.m_val));
}

// Returns bm1 - bm2
BigM sub_BigM(BigM bm1, BigM bm2) {
    return new_BigM(fraction_subtract(bm1.num_val, bm2.num_val), fraction_subtract(bm1.m_val, bm2.m_val));
}

// Returns bm1 * bm2, assumig it is valid.
// If not valid, will exit.
BigM mul_BigM(BigM bm1, BigM bm2) {
    if (fraction_is_zero(bm2.num_val) && !fraction_is_zero(bm2.m_val) && fraction_is_zero(bm1.m_val)) {
        return new_BigM(fraction_zero(), fraction_multiply(bm1.num_val, bm2.m_val));
    }
    if (!fraction_is_zero(bm2.m_val)) {
        char *str = malloc(25 * sizeof(char));
        printf("Attempt to multiply ");
        printf("%s", BigM_str(bm1, str));
        printf(" by ");
        printf("%s", BigM_str(bm2, str));
        printf(", which has non-zero M value");
        free(str);
        exit(EXIT_FAILURE);
    }
    return new_BigM(fraction_multiply(bm1.num_val, bm2.num_val), fraction_multiply(bm1.m_val, bm2.num_val));
}

// Returns bm1 / bm2, assuming valid.
// Otherwise, will exit.
BigM div_BigM(BigM bm1, BigM bm2) {
    if (fraction_is_zero(bm1.num_val) && fraction_is_zero(bm2.num_val)) {
        if (!fraction_is_zero(bm1.m_val) && !fraction_is_zero(bm2.m_val)) {
            return new_BigM(fraction_divide(bm1.m_val, bm2.m_val), fraction_zero());
        }
    }
    if (!fraction_is_zero(bm2.m_val)) {
        char *str = malloc(25 * sizeof(char));
        printf("Attempt to divide by ");
        printf("%s", BigM_str(bm2, str));
        printf(", which has non-zero M value");
        free(str);
        exit(EXIT_FAILURE);
    }
    return new_BigM(fraction_divide(bm1.num_val, bm2.num_val), fraction_divide(bm1.m_val, bm2.num_val));
}

// Returns true if bm1 == bm2
bool BigM_eq(BigM bm1, BigM bm2) {
    return fraction_eq(bm1.m_val, bm2.m_val) && fraction_eq(bm1.num_val, bm2.num_val);
}

// Returns true if bm1 != bm2
bool BigM_ne(BigM bm1, BigM bm2) {
    return fraction_ne(bm1.m_val, bm2.m_val) || fraction_ne(bm1.num_val, bm2.num_val);
}

// Returns true if a < b
bool BigM_lt(BigM* a, BigM* b) {
    if (fraction_gt(b->m_val, a->m_val)) {
        return true;
    } else if (fraction_eq(b->m_val, a->m_val)) {
        return fraction_gt(b->num_val, a->num_val);
    } else {
        return false;
    }
}

// Returns true if a <= b
bool BigM_le(BigM* a, BigM* b) {
    if (fraction_eq(a->m_val, b->m_val)) {
        return fraction_lte(a->num_val, b->num_val);
    } else if (fraction_lt(a->m_val, b->m_val)) {
        return true;
    } else {
        return false;
    }
}

// Returns true if a > b
bool BigM_gt(BigM* a, BigM* b) {
    if (fraction_lt(b->m_val, a->m_val)) {
        return true;
    } else if (fraction_eq(b->m_val, a->m_val)) {
        return fraction_lt(b->num_val, a->num_val);
    } else {
        return false;
    }
}

// Returns true if a >= b
bool BigM_ge(BigM* a, BigM* b) {
    if (fraction_eq(a->m_val, b->m_val)) {
        return fraction_gte(a->num_val, b->num_val);
    } else if (fraction_gt(a->m_val, b->m_val)) {
        return true;
    } else {
        return false;
    }
}