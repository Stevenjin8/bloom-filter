#include <errno.h>
#include <memory.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include "bf.h"

#define LN2 0.69314718056
#define N_WORDS 370100

/**
 * Prints running time (in us), number of unfiltered items, size of array
 * arguments are file with dictionary, number of hash functions.
 * Array size is chosen automatically.
 */
int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Incorrect number of arguments.\n");
        return 1;
    }
    char *dict_name = argv[1];
    FILE *dictionary = fopen(dict_name, "r");
    if (dictionary == NULL) {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return 1;
    }

    struct bloom_filter bf;
    size_t k = atoll(argv[2]);
    if (k == 0) {
        fprintf(stderr, "atoll: %s\n", strerror(errno));
        return 1;
    }
    size_t size = (size_t)((double)k * (double)N_WORDS / LN2);
    struct timeval insertion_start, insertion_end;
    bf_init(&bf, size, k);

    char line[1024];
    gettimeofday(&insertion_start, DST_NONE);
    while (fgets(line, sizeof(line), dictionary)) {
        // We can ignore trailing newline
        // Assume no errors
        bf_add(&bf, line);
    }
    gettimeofday(&insertion_end, DST_NONE);
    fclose(dictionary);

    struct timeval lookup_start, lookup_end;
    size_t count = 0;
    gettimeofday(&lookup_start, DST_NONE);
    while (fgets(line, sizeof(line), stdin)) {
        // We can ignore trailing newline
        if (!bf_contains(&bf, line)) {
            count++;
        }
    }
    gettimeofday(&lookup_end, DST_NONE);

    // the diff in seconds should be small so we won't overflow.
    size_t lookup_diff = (lookup_end.tv_sec - lookup_start.tv_sec) * 1000000 + lookup_end.tv_usec -
                         lookup_start.tv_usec;
    size_t insertion_diff = (lookup_end.tv_sec - lookup_start.tv_sec) * 1000000 +
                            lookup_end.tv_usec - insertion_start.tv_usec;
    // Execution time, number of duplicates, number of hash functions, array size in bits.
    printf("%ld,%lu,%lu,%lu,%lu\n", lookup_diff, count, k, size, insertion_diff);
}
