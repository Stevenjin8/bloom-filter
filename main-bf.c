#include <errno.h>
#include <memory.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdint.h>

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
    bf_init(&bf, size, k);

    char line[1024];
    while (fgets(line, sizeof(line), dictionary)) {
        // We can ignore trailing newline
        // Assume no errors
        bf_add(&bf, line);
    }
    fclose(dictionary);

    struct timeval start, end;
    size_t count = 0;
    gettimeofday(&start, DST_NONE);
    while (fgets(line, sizeof(line), stdin)) {
        // We can ignore trailing newline
        if (!bf_contains(&bf, line)) {
            count++;
        }
    }
    gettimeofday(&end, DST_NONE);

    // the diff in seconds should be small so we won't overflow.
    size_t diff = (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;
    // Execution time, number of duplicates, number of hash functions, array size in bits.
    printf("%ld,%lu,%lu,%lu\n", diff, count, k, size);
}
