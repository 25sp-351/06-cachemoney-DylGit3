#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cache.h"
#include "money_to_string.h"

int main() {
    cache_load();

    ProviderFunction provider = convert_to_words;
    provider                  = set_provider(convert_to_words);

    char buffer_line[MAX_LINE_LENGTH];

    FILE *output_file = fopen("output.txt", "w");
    if (!output_file) {
        fprintf(stderr, "Error opening output file.\n");
        exit(1);
    }

    while (fgets(buffer_line, sizeof(buffer_line), stdin)) {
        long long money = -1;

        if (sscanf(buffer_line, "%llu", &money) == 1) {
            int dollar_check = money / 100;
            if (dollar_check >= 0 && dollar_check <= MAX_MONEY_INTAKE) {
                char *dollars_text = (*provider)(money);

                fprintf(output_file, "%llu = %s\n", money, dollars_text);
                printf("%llu = %s\n", money, dollars_text);
            }
        }
    }

    fclose(output_file);

    cache_clear();

    return 0;
}
