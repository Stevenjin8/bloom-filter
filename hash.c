#include "hash.h"

#include <stdint.h>

size_t hash(char *str, size_t h) {
    uint8_t *p;

    // thanks windows
    for (p = (uint8_t *)str; (*p != '\0') && (*p != '\n') && (*p != '\r'); p++) {
        h = 37 * h + *p;
    }
    return h;
}

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
