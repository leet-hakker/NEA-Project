#ifndef INPUT_VALIDATION_H
#define INPUT_VALIDATION_H
#include <stdbool.h>
#include "fraction.h"
#include "bigm.h"

char **string_to_bigm_parts(const char *string);
Fraction string_to_fraction(char *string);
BigM string_to_bigm(char *string);
bool validate_input(char *current_string, char character);

#endif // INPUT_VALIDATION_H