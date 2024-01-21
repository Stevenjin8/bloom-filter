#include <errno.h>
#include <memory.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include "trie.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Incorrect number of arguments.\n");
        return 1;
    }
    char *dict_name = argv[1];
    FILE *dictionary = fopen(dict_name, "r");
    if (dictionary == NULL) {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return 1;
    }

    struct trie trie;
    trie_init(&trie);

    char line[1024];
    while (fgets(line, sizeof(line), dictionary)) {
        // We can ignore trailing newline
        trie_add(&trie, line);
    }

    struct timeval start;
    struct timeval end;
    size_t count = 0;
    gettimeofday(&start, DST_NONE);
    while (fgets(line, sizeof(line), stdin)) {
        // We can ignore trailing newline
        if (!trie_contains(&trie, line)) {
            // write(1, line, strlen(line));
            count++;
        }
    }
    gettimeofday(&end, DST_NONE);
    printf("Took %ld microseconds\n", end.tv_usec - start.tv_usec);
    printf("Found %lu duplicates\n", count);
}
