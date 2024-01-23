#ifndef __CC_H
#define __CC_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define CC_N_BINS 3

struct cc_bin {
    uint8_t size;
    uint32_t items[CC_N_BINS];
};

struct cc_filter {
    uint32_t fingerprint_mask;
    size_t n_bins;
    struct cc_bin* bins;
};

struct cc_filter *cc_init(struct cc_filter* cc, size_t fingerprint_size, size_t log2_n_bins);

int cc_add(struct cc_filter* cc, char* str);

bool cc_contains(struct cc_filter* cc, char* str);

#endif
