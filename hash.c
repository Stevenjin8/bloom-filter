#include "hash.h"

#include <stdint.h>

/**
 * Inspired by djb2
 * http://www.cse.yorku.ca/~oz/hash.html
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

/**
 * Inspired by FNV hash
 * http://www.isthe.com/chongo/tech/comp/fnv/index.html#google_vignette
 */
size_t hash2(char *str, size_t h) {
    uint8_t *p;

    // thanks windows
    size_t i = 0;
    for (p = (uint8_t *)str; (*p != '\0') && (*p != '\n') && (*p != '\r'); p++) {
        h = h + i * (*p) * 37;
        h = h * 37;
        i++;
    }
    return h;
}

size_t hash_n(size_t n) {
    return n * 37;
}
