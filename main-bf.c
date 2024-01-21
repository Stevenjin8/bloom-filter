#include <errno.h>
#include <memory.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include "bf.h"

#define LN2 0.69314718056

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
    size_t n_words = 370100;
    size_t k = atoll(argv[2]);
    size_t size = (size_t)((double) k * (double) n_words / LN2);
    printf("Using array of size %lu.\n", size);
    bf_init(&bf, size, k);

    char line[1024];
    while (fgets(line, sizeof(line), dictionary)) {
        // We can ignore trailing newline
        bf_add(&bf, line);
    }

    struct timeval start;
    struct timeval end;
    size_t count = 0;
    gettimeofday(&start, DST_NONE);
    while (fgets(line, sizeof(line), stdin)) {
        // We can ignore trailing newline
        if (!bf_contains(&bf, line)) {
            // Use straight syscall so we jump right into kernel mode and printf overhead
            // is not part of the performance benchmarks.
            count++;
        }
    }
    gettimeofday(&end, DST_NONE);
    printf("Took %ld microseconds\n", end.tv_usec - start.tv_usec);
    printf("Found %lu duplicates\n", count);
}
