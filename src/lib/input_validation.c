#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "../../include/fraction.h"
#include "../../include/bigm.h"

// Returns true if the given `character is in
// the given `string`, and false otherwise.
bool character_in_string(const char *string, const char character) {
    for (int i=0; i < strlen(string); i++) {
        if (string[i] == character) {
            return true;
        }
    }
    return false;
}

// Splits the given `string` accross the given
// `delimiter`, returning an array containing
// these chunks.
char **split_string(const char *string, const char delimiter, int *num_chunks) {

    // Count the number of delimiters in the given
    // `string`.
    int count = 0;
    for (int i=0; i < strlen(string); i++) {
        if (string[i] == delimiter) {
            count++;
        }
    }

    // Allocate count + 1, as there will likely be
    // chunks on either side of the delimiter
    char **array = calloc(count + 1, sizeof(char*));

    if (count == 0) {
        array[0] = strdup(string);
        return array;
    }

    // Make a copy as we do not want to modify
    // the original string.
    char *copy = strdup(string);

    char delimiter_string[2];
    delimiter_string[0] = delimiter;
    delimiter_string[1] = '\0';

    char *chunk = strtok(copy, delimiter_string);
    int i = 0;
    while (chunk != NULL) {
        array[i++] = strdup(chunk);

        // Passing NULL here gets the last used
        // pointer from the function, in this case
        // `copy`
        chunk = strtok(NULL, delimiter_string);
    }

    *num_chunks = i;

    free(copy);
    free(chunk);

    return array;
}

// Returns a copy of the given `string`, with the given `character`
// removed
char *remove_character_from_string(const char *string, const char character) {

    // Make a copy as we don't want to modify the original
    char *copy = strdup(string);
    int i, j;
    for (i = j = 0; i < strlen(copy); i++) {
        if (copy[i] != character) {
            copy[j++] = copy[i];
        }
    }
    copy[j] = '\0';

    return copy;
}

// Replace given `character` in given `string` with
// given `replace_with`, and return the resulting string.
char *replace_character(char *string, char character, char replace_with) {
    char *copy = strdup(string);
    for (int i = 0; i < strlen(copy); i++) {
        if (copy[i] == character) {
            copy[i] = replace_with;
        }
    }

    return copy;
}

// Returns `true` if the given `string`
// is a number, and `false` otherwise.
bool isnumeric(const char *string) {
    if (character_in_string("-+", string[0])) {
        // We don't allocate strlen(string)-1 because space
        // is needed for the null terminator.
        char *signless_string = calloc(strlen(string), sizeof(char));
        strncpy(signless_string, string + 1, strlen(string)-1);
        for (int i=0; i < strlen(signless_string); i++) {
            if (!isdigit(signless_string[i])) {
                free(signless_string);
                return false;
            }
        }
        free(signless_string);
        return true;
    } else {
        for (int i=0; i < strlen(string); i++) {
            if (!isdigit(string[i])) {
                return false;
            }
        }
        return true;
    }
}

// Splits the given string into it's corresponding
// num_val and m_val parts.
char **string_to_bigm_parts(const char *string) {
    // Each of these values could end up the entire
    // size of the given string, so we allocate
    // the appropriate size to all of them.
    char *num_part = calloc(strlen(string)+1, sizeof(char));
    char *m_part = calloc(strlen(string)+1, sizeof(char));
    char *temp = calloc(strlen(string)+1, sizeof(char));

    // Iterate through the string, checking each character
    for (int char_index=0; char_index < strlen(string); char_index++) {
        if (character_in_string("-+", string[char_index])) {
            // If the character occurs past the start
            // of the string, this means we can move to
            // the m part of the number
            if (char_index > 0) {
                strcpy(num_part, temp);
                strcpy(temp, &string[char_index]);
                temp[1] = '\0';
            } else {
                strncat(temp, &string[char_index], 1);
            }
        } else {
            strncat(temp, &string[char_index], 1);
        }
    }

    // If num_part has data, then whatever is in
    // `temp` must be the m part
    if (strlen(num_part) > 0) {
        strcpy(m_part, temp);
    }
    // Otherwise, whatever is in temp can be moved
    // into num_part
    else {
        strcpy(num_part, temp);
    }

    free(temp);

    // num_part may contain an M value
    // (e.g. if the string is "4M")
    // so correct that, and set num_part
    // to be zero
    if (character_in_string(num_part, 'M')) {
        strcpy(m_part, num_part);
        strcpy(num_part, "0\0");
    }

    if (strlen(m_part) == 0) {
        strcpy(m_part, "0\0");
    }

    char **parts_list = malloc(sizeof(char*)*2);

    parts_list[0] = num_part;
    parts_list[1] = m_part;

    return parts_list;
}

// Converts the given string into a Fraction
Fraction string_to_fraction(char *string) {
    // Important special cases
    if (string == "-") {
        string = "-1";
    } if (string == "+") {
        string = "1";
    } if (string == "") {
        string = "1";
    }

    int _ = 0;
    // Split the fraction into its components
    char **result = split_string(string, '/', &_);

    int numerator = atoi(result[0]);
    free(result[0]);
    int denominator = 1;
    // This case is when the string actually
    // contained a "/"
    if (_ > 1) {
        denominator = atoi(result[1]);
        free(result[1]);
    }

    free(result);

    return new_fraction(numerator, denominator);
}

// Converts the given string into a BigM value
BigM string_to_bigm(char *string) {
    char **parts = string_to_bigm_parts(string);
    
    // Initial values for each part, as they
    // may not get set, which corresponds to
    // them being zero
    Fraction num = new_fraction(0, 1);
    Fraction m_part = new_fraction(0, 1);

    num = string_to_fraction(parts[0]);

    char *m_removed = remove_character_from_string(parts[1], 'M');
    char *plus_removed = remove_character_from_string(m_removed, '+');
    free(m_removed);

    if (strlen(plus_removed) == 0) {
        m_part = new_fraction(1, 1);
    } else if (strcmp(plus_removed, "-") == 0) {
        m_part = new_fraction(-1, 1);
    } else {
        m_part = string_to_fraction(plus_removed);
    }

    free(plus_removed);

    return new_BigM(num, m_part);
}

// Returns true if the given character is valid to type
// next, given the current state of the string.
bool validate_input(char *current_string, char character) {
    // Always allow input if the string is empty,
    // except '/' as the input cannot start with that
    if (!strlen(current_string)) {
        return character != '/';
    }

    // "M" is only ever allowed to be the final
    // character, so nothing may come after
    if (current_string[strlen(current_string)-1] == 'M') {
        return false;
    }
    
    // If the last character in the string is a
    // digit
    if (isdigit(current_string[strlen(current_string)-1])) {
        char *replaced_string = replace_character(current_string, '-', '+');
        int n_chunks = 0;
        char **split = split_string(replaced_string, '+', &n_chunks);
        free(replaced_string);
        // If the user is trying to add "/"
        // to the end of the string, then
        // it needs to be ensured that they
        // are not at the denominator of a fraction
        // already.
        if (character == '/') {
            // If the last chunk contains a "/" then
            // it is a complete fraction, so return
            // False
            if (character_in_string(split[n_chunks-1], '/')) {
                for (int i=0; i < n_chunks; i++) {
                    free(split[i]);
                }
                free(split);
                return false;
            }
        }
        
        // If there are more than one chunks (i.e. two)
        // then the user may not add any more,
        // so if the user wants to enter "+" or "-"
        // then return False
        // printf("%d\n", n_chunks);
        if (n_chunks > 1) {
            if (character_in_string("+-", character)) {
                for (int i=0; i < n_chunks; i++) {
                    free(split[i]);
                }
                free(split);
                return false;
            }
        }
        for (int i=0; i < n_chunks; i++) {
            free(split[i]);
        }
        free(split);
        return true;
    }
    
    // If the last character the user typed
    // is "/", then the only valid input now
    // must be to write a denominator
    int length = strlen(current_string);
    if (current_string[length-1] == '/') {
        return isdigit(character);
    }
    
    if (character_in_string("+-", current_string[length-1])) {
        return isdigit(character) || character == 'M';
    }


    return false;
}