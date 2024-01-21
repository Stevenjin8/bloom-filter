#include "bf.h"

#include <errno.h>
#include <memory.h>
#include <stdint.h>
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
    uint8_t *p;

    // thanks windows
    for (p = (uint8_t *)str; (*p != '\0') && (*p != '\n') && (*p != '\r'); p++) {
        h = 37 * h + *p;
    }
    return h;
}

void bf_add(struct bloom_filter *bf, char *str) {
    for (size_t i = 0; i < bf->k; i++) {
        size_t index = hash(str, i) % bf->size;
        uint8_t *byte = &bf->filter[index / 8];
        *byte = *byte | (1u << (index % 8));
    }
}

void bf_init(struct bloom_filter *bf, size_t size, size_t k) {
    memset(bf, 0, sizeof(*bf));
    bf->size = size; /* in bits */
    bf->k = k;
    bf->filter = malloc(size / 8 + 1);
    memset(bf->filter, 0, size / 8 + 1);
}

bool bf_contains(struct bloom_filter *bf, char *str) {
    for (size_t i = 0; i < bf->k; i++) {
        size_t index = hash(str, i) % bf->size;
        uint8_t byte = bf->filter[index / 8];
        if ((byte & (1u << (index % 8))) == 0) {
            return false;
        }
    }
    return true;
}
