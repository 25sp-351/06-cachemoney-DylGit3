#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cache.h"
#include "money_to_string.h"

int main() {
    LoadFunction load_the_cache     = cache_load;
    LookupFunction search_for_value = cache_lookup;
    InsertFunction insert_a_value   = cache_insert;

    load_the_cache();

    money_to_string();

    return 0;
}
