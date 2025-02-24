#include "money_to_string.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cache.h"

char *single_digits[10] = {"zero", "one", "two",   "three", "four",
                           "five", "six", "seven", "eight", "nine"};
char *teen_digits[10]   = {"ten",      "eleven",  "twelve",  "thirteen",
                           "fourteen", "fifteen", "sixteen", "seventeen",
                           "eighteen", "nineteen"};
char *tens_digits[10]   = {"",      "",      "twenty",  "thirty", "forty",
                           "fifty", "sixty", "seventy", "eighty", "ninety"};
char *thousands[4]      = {"", "thousand", "million", "billion"};

char *helper(long long num) {
    static char result[MAX_LINE_LENGTH];
    memset(result, 0, sizeof(result));

    if (num >= 100) {
        strncat(result, single_digits[num / 100],
                MAX_LINE_LENGTH - strlen(result) - 1);
        strncat(result, " hundred ", MAX_LINE_LENGTH - strlen(result) - 1);
        num %= 100;
    }

    if (num >= 10 && num < 20) {
        strncat(result, teen_digits[num - 10],
                MAX_LINE_LENGTH - strlen(result) - 1);
    } else if (num >= 20) {
        strncat(result, tens_digits[num / 10],
                MAX_LINE_LENGTH - strlen(result) - 1);
        if (num % 10 != 0) {
            strncat(result, "-", MAX_LINE_LENGTH - strlen(result) - 1);
            strncat(result, single_digits[num % 10],
                    MAX_LINE_LENGTH - strlen(result) - 1);
        }
    } else if (num > 0) {
        strncat(result, single_digits[num],
                MAX_LINE_LENGTH - strlen(result) - 1);
    }

    return result;
}

// This returns an allocated string, caller must free it
char *convert_to_words(long long money) {
    int dollars         = money / 100;
    int remaining_cents = money % 100;
    char *result        = malloc(MAX_LINE_LENGTH);
    if (result == NULL)
        return NULL;
    result[0] = '\0';

    if (dollars >= 1000000000) {
        strncat(result, helper(dollars / 1000000000),
                MAX_LINE_LENGTH - strlen(result) - 1);
        strncat(result, " ", MAX_LINE_LENGTH - strlen(result) - 1);
        strncat(result, thousands[3], MAX_LINE_LENGTH - strlen(result) - 1);
        strncat(result, " ", MAX_LINE_LENGTH - strlen(result) - 1);
        dollars %= 1000000000;
    }

    if (dollars >= 1000000) {
        strncat(result, helper(dollars / 1000000),
                MAX_LINE_LENGTH - strlen(result) - 1);
        strncat(result, " ", MAX_LINE_LENGTH - strlen(result) - 1);
        strncat(result, thousands[2], MAX_LINE_LENGTH - strlen(result) - 1);
        strncat(result, " ", MAX_LINE_LENGTH - strlen(result) - 1);
        dollars %= 1000000;
    }

    if (dollars >= 1000) {
        strncat(result, helper(dollars / 1000),
                MAX_LINE_LENGTH - strlen(result) - 1);
        strncat(result, " ", MAX_LINE_LENGTH - strlen(result) - 1);
        strncat(result, thousands[1], MAX_LINE_LENGTH - strlen(result) - 1);
        strncat(result, " ", MAX_LINE_LENGTH - strlen(result) - 1);
        dollars %= 1000;
    }

    if (dollars > 0) {
        strncat(result, helper(dollars), MAX_LINE_LENGTH - strlen(result) - 1);
    }

    if (dollars == 1) {
        strncat(result, " dollar and ", MAX_LINE_LENGTH - strlen(result) - 1);
    } else if (dollars > 1) {
        strncat(result, " dollars and ", MAX_LINE_LENGTH - strlen(result) - 1);
    }

    if (remaining_cents == 0) {
        strncat(result, "zero cents", MAX_LINE_LENGTH - strlen(result) - 1);
    } else {
        strncat(result, helper(remaining_cents),
                MAX_LINE_LENGTH - strlen(result) - 1);
        if (remaining_cents == 1) {
            strncat(result, " cent", MAX_LINE_LENGTH - strlen(result) - 1);
        } else {
            strncat(result, " cents", MAX_LINE_LENGTH - strlen(result) - 1);
        }
    }

    return result;
}
