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
        strcat(result, single_digits[num / 100]);
        strcat(result, " hundred ");
        num %= 100;
    }

    if (num >= 10 && num < 20) {
        strcat(result, teen_digits[num - 10]);
    } else if (num >= 20) {
        strcat(result, tens_digits[num / 10]);
        if (num % 10 != 0) {
            strcat(result, "-");
            strcat(result, single_digits[num % 10]);
        }
    } else if (num > 0) {
        strcat(result, single_digits[num]);
    }

    return result;
}

char *convert_to_words(long long money) {
    // if (money < MEMOIZED_ARRAY && cache[money]) {
    //     return cache[money];
    // }

    int dollars         = money / 100;
    int remaining_cents = money % 100;
    static char result[MAX_LINE_LENGTH];
    result[0] = '\0';

    if (dollars >= 1000000000) {
        strcat(result, helper(dollars / 1000000000));
        strcat(result, " ");
        strcat(result, thousands[3]);
        strcat(result, " ");
        dollars %= 1000000000;
    }

    if (dollars >= 1000000) {
        strcat(result, helper(dollars / 1000000));
        strcat(result, " ");
        strcat(result, thousands[2]);
        strcat(result, " ");
        dollars %= 1000000;
    }

    if (dollars >= 1000) {
        strcat(result, helper(dollars / 1000));
        strcat(result, " ");
        strcat(result, thousands[1]);
        strcat(result, " ");
        dollars %= 1000;
    }

    if (dollars > 0) {
        strcat(result, helper(dollars));
    }

    if (dollars == 1) {
        strcat(result, " dollar and ");
    } else if (dollars > 1) {
        strcat(result, " dollars and ");
    }

    if (remaining_cents == 0) {
        strcat(result, "zero cents");
    } else {
        strcat(result, helper(remaining_cents));
        if (remaining_cents == 1) {
            strcat(result, " cent");
        } else {
            strcat(result, " cents");
        }
    }

    // if (money < MEMOIZED_ARRAY) {
    //     cache[money] = strdup(result);
    // }

    return result;
}

void money_to_string() {
    char buffer_line[MAX_LINE_LENGTH];
    // char **cache = load_cache();

    FILE *output_file = fopen("output.txt", "w");
    // FILE *cache_file  = fopen(MEMOIZED_FILE, "a");
    if (!output_file) {
        fprintf(stderr, "Error opening output file.\n");
        return;
    }
    // if (!cache_file) {
    //     fprintf(stderr, "Error opening cache file.\n");
    //     fclose(output_file);
    //     return;
    // }

    while (fgets(buffer_line, sizeof(buffer_line), stdin)) {
        long long money = -1;

        if (sscanf(buffer_line, "%llu", &money) == 1) {
            int dollar_check = money / 100;
            if (dollar_check >= 0 && dollar_check <= MAX_MONEY_INTAKE) {
                char *dollars_text = convert_to_words(money);

                fprintf(output_file, "%llu = %s\n", money, dollars_text);
                printf("%llu = %s\n", money, dollars_text);

                // if (money >= 0 && money <= 150000 && cache[money] == NULL) {
                //     fprintf(cache_file, "%llu = %s\n", money, dollars_text);
                // }
            }
        }
    }

    fclose(output_file);
    // fclose(cache_file);
}
