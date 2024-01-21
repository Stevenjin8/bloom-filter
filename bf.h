#ifndef __BF_H 
#define __BF_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

struct bloom_filter {
    size_t size;
    uint8_t *filter;
    size_t k;
};

void bf_add(struct bloom_filter *bf, char *str);

bool bf_contains(struct bloom_filter *bf, char *str);

void bf_init(struct bloom_filter *bf, size_t size, size_t k);

#endif
