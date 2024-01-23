#include "bf.h"

#include <errno.h>
#include <memory.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "hash.h"

#define SALT "zz"

void bf_add(struct bloom_filter *bf, char *str) {
    // rather than starting with different values, keep adding to postfix
    size_t running_index = hash(str, 0);
    for (size_t i = 0; i < bf->k; i++) {
        running_index = hash(SALT, running_index);
        size_t index = running_index % bf->size;
        uint8_t *byte = &bf->filter[index / 8];
        *byte = *byte | (1u << (index % 8));
    }
}

/**
 * size is in bits
 * k number of hash functions
 */
void bf_init(struct bloom_filter *bf, size_t size, size_t k) {
    memset(bf, 0, sizeof(*bf));
    bf->size = size; /* in bits */
    bf->k = k;
    bf->filter = malloc(size / 8 + 1);
    memset(bf->filter, 0, size / 8 + 1);
}

bool bf_contains(struct bloom_filter *bf, char *str) {
    size_t running_index = hash(str, 0);
    for (size_t i = 0; i < bf->k; i++) {
        running_index = hash(SALT, running_index);
        size_t index = running_index % bf->size;
        uint8_t byte = bf->filter[index / 8];
        if ((byte & (1u << (index % 8))) == 0) {
            return false;
        }
    }
    return true;
}
