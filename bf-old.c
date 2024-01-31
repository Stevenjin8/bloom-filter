#include "bf.h"

#include <errno.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * str: the string to hash
 * h:   initial seed value
 *
 * stops at end of string or newline.
 *
 * https://stackoverflow.com/questions/2351087/what-is-the-best-32bit-hash-function-for-short-strings-tag-names
 */
size_t hash(char *str, size_t h) {
    unsigned char *p;

    // thanks windows
    for (p = (unsigned char *)str; (*p != '\0') && (*p != '\n') && (*p != '\r'); p++) {
        h = 37 * h + *p;
    }
    return h;
}

/**
 * Add element to bloom filter
 */
void bf_add(struct bloom_filter *bf, char *str) {
    for (size_t i = 0; i < bf->k; i++) {
        size_t index = hash(str, i) % bf->size;
        bf->filter[index] = 1;
    }
}

/**
 * Initialize bloom filter
 */
void bf_init(struct bloom_filter *bf, size_t size, size_t k) {
    memset(bf, 0, sizeof(*bf));
    bf->size = size;
    bf->k = k;
    bf->filter = malloc(size);
    memset(bf->filter, 0, size);
}

/**
 * Check if Bloom Filter contains items
 */
bool bf_contains(struct bloom_filter *bf, char *str) {
    for (size_t i = 0; i < bf->k; i++) {
        size_t index = hash(str, i) % bf->size;
        if (bf->filter[index] == 0) {
            return false;
        }
    }
    return true;
}
