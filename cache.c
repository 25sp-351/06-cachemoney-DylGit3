#include "cache.h"

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CacheEntry cache[CACHE_SIZE];

static ProviderFunction downstream_provider;

void cache_load(void) {
    for (int ix = 0; ix < CACHE_SIZE; ++ix) {
        cache[ix].key   = UNDEFINED_KEY;
        cache[ix].value = NULL;
    }

    FILE *cachefile = fopen(CACHE_FILE, "r");
    if (!cachefile) {
        fprintf(stderr, "Error opening the cache file\n");
        exit(1);
    }

    int index = 0;
    char line[BUFFER];
    while (index < CACHE_SIZE && fgets(line, sizeof(line), cachefile) != NULL) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        long long key;
        char value[BUFFER];
        if (sscanf(line, "%lld = %[^\n]", &key, value) == 2) {
            char *new_value = malloc(strlen(value) + 1);
            if (new_value != NULL) {
                strcpy(new_value, value);
                cache_insert(key, new_value);
            }
        }
    }
    fclose(cachefile);
}

void cache_insert(KeyType insert_key, ValueType insert_value) {
    if (cache[0].key == -1) {
        cache[0].key   = insert_key;
        cache[0].value = insert_value;
        return;
    }

    if (cache[CACHE_SIZE - 1].key != -1)
        cache_free_end();

    for (int ix = CACHE_SIZE - 1; ix > 0; --ix) {
        cache[ix] = cache[ix - 1];
    }

    cache[0].key   = insert_key;
    cache[0].value = insert_value;
}

ValueType cache_lookup(KeyType lookup_key) {
    for (int ix = 0; ix < CACHE_SIZE; ++ix) {
        if (cache[ix].value != NULL && cache[ix].key == lookup_key) {
            return cache[ix].value;
        }
    }

    ValueType output = (*downstream_provider)(lookup_key);
    cache_insert(lookup_key, output);
    return output;
}

ProviderFunction set_provider(ProviderFunction downstream) {
    fprintf(stderr, __FILE__ " set_provider()\n");
    downstream_provider = downstream;
    return cache_lookup;
}

// Call at the end of the main function
void cache_clear(void) {
    FILE *cachefile = fopen(CACHE_FILE, "w");
    if (!cachefile)
        fprintf(stderr, "Error printing to %s.\n", CACHE_FILE);
    for (int ix = 0; ix < CACHE_SIZE; ++ix) {
        if (cache[ix].key == -1)
            break;
        fprintf(cachefile, "%lld = %s\n", cache[ix].key, cache[ix].value);
    }
    fclose(cachefile);

    for (int ix = 0; ix < CACHE_SIZE; ++ix) {
        if (cache[ix].value != NULL) {
            free(cache[ix].value);
            cache[ix].value = NULL;
        }
    }
}

void cache_free_end(void) {
    cache[CACHE_SIZE - 1].key = -1;
    free(cache[CACHE_SIZE - 1].value);
    cache[CACHE_SIZE - 1].value = NULL;
}
