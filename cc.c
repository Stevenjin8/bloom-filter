#include "cc.h"

#include <memory.h>
#include <stdio.h>

#include "hash.h"

#define CC_FINGERPRINT_SEED 7879
#define CC_HASH_SEED 1
#define CC_LOOP_MAX 200000

struct cc_filter* cc_init(struct cc_filter* cc, size_t fingerprint_size, size_t log2_n_bins) {
    memset(cc, 0, sizeof(*cc));
    cc->fingerprint_mask = (1ull << fingerprint_size) - 1;
    cc->n_bins = 1ull << log2_n_bins;
    // calloc sets everything to 0.
    if (!(cc->bins = calloc(sizeof(struct cc_bin), cc->n_bins))) {
        return NULL;
    }
    return cc;
}

void cc_bin_add(struct cc_bin* bin, uint32_t fingerprint) {
    for (size_t i = bin->size; i > 0; i--) {
        bin->items[i] = bin->items[i - 1];
    }
    bin->items[0] = fingerprint;
    bin->size++;
}

uint32_t cc_bin_remove(struct cc_bin* bin) {
    bin->size--;
    return bin->items[bin->size];
}

bool cc_contains(struct cc_filter* cc, char* str) {
    uint32_t fingerprint = hash(str, CC_FINGERPRINT_SEED) & cc->fingerprint_mask;
    uint32_t h1 = hash2(str, CC_HASH_SEED) % cc->n_bins;
    uint32_t h2 = (h1 ^ hash_n(fingerprint)) % cc->n_bins;

    struct cc_bin* bin1 = &cc->bins[h1];
    struct cc_bin* bin2 = &cc->bins[h2];
    for (size_t i = 0; i < bin1->size; i++) {
        if (fingerprint == bin1->items[i]) {
            return true;
        }
    }
    for (size_t i = 0; i < bin2->size; i++) {
        if (fingerprint == bin2->items[i]) {
            return true;
        }
    }
    return false;
}

int cc_add(struct cc_filter* cc, char* str) {
    // obtain fingerprint
    if (cc_contains(cc, str)) {
        return 0;
    }
    uint32_t fingerprint = hash(str, CC_FINGERPRINT_SEED) & cc->fingerprint_mask;
    uint32_t h1 = hash2(str, CC_HASH_SEED) % cc->n_bins;
    uint32_t h2 = (h1 ^ hash_n(fingerprint)) % cc->n_bins;
    struct cc_bin* bin = &cc->bins[h1];
    if (bin->size < CC_N_BINS) {
        // there is room in bin, add
        cc_bin_add(bin, fingerprint);
        return 0;
    }
    // cuckoo cycle
    for (size_t i = 0; i < CC_LOOP_MAX; i++) {
        bin = &cc->bins[h2];
        if (bin->size < CC_N_BINS) {
            // there is room in bin, add
            cc_bin_add(bin, fingerprint);
            return 0;
        }
        // here, the second bin is full
        uint32_t new_fingerprint = cc_bin_remove(bin);     // make some room
        cc_bin_add(bin, fingerprint);                      // add new fingerprint
        h2 = (h2 ^ hash_n(new_fingerprint)) % cc->n_bins;  // find next location for new fingerprint
        fingerprint = new_fingerprint;                     // prep for new loop
    }
    return 1;
}
