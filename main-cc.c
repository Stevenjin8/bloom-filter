#include <errno.h>
#include <memory.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include "cc.h"
#include "hash.h"

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "Incorrect number of arguments.\n");
        return 1;
    }
    char *dict_name = argv[1];
    FILE *dictionary = fopen(dict_name, "r");
    if (dictionary == NULL) {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return 1;
    }

    struct cc_filter cc;

    size_t fingerprint_size;
    size_t log_n_bins;
    if ((fingerprint_size = atoll(argv[2])) == 0) {
        fprintf(stderr, "Bad fingerprint size\n");
        return 1;
    }
    if ((log_n_bins = atoll(argv[3])) == 0) {
        fprintf(stderr, "Bad log_n_bins\n");
        return 1;
    }

    // second arg max 24
    cc_init(&cc, fingerprint_size, log_n_bins);

    char line[1024];
    while (fgets(line, sizeof(line), dictionary)) {
        // We can ignore trailing newline
        // Assume this works
        if (cc_add(&cc, line)) {
            fprintf(stderr, "Failure to add %s\n", line);
            return 1;
        }
    }
    fclose(dictionary);

    struct timeval start;
    struct timeval end;
    size_t count = 0;
    gettimeofday(&start, DST_NONE);
    while (fgets(line, sizeof(line), stdin)) {
        // We can ignore trailing newline
        if (!cc_contains(&cc, line)) {
            // write(1, line, strlen(line));
            count++;
        }
    }
    gettimeofday(&end, DST_NONE);
    size_t diff = (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;
    printf("%ld,%lu,%lu,%lu\n", diff, count, fingerprint_size,
           fingerprint_size * (1lu << log_n_bins) * CC_N_BINS);
    free(cc.bins);
}
