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
    size_t total = 0;
    struct timeval insertion_start, insertion_end;
    gettimeofday(&insertion_start, DST_NONE);
    while (fgets(line, sizeof(line), dictionary)) {
        // We can ignore trailing newline
        // Assume this works
        int added = trie_add(&trie, line);
        if (added == -1) {
            fprintf(stderr, "Entry contains invalid characters: %s", line);
            return 1;
        }
        total = total + added;
    }
    gettimeofday(&insertion_end, DST_NONE);
    fclose(dictionary);

    struct timeval lookup_start, lookup_end;
    size_t count = 0;
    gettimeofday(&lookup_start, DST_NONE);
    while (fgets(line, sizeof(line), stdin)) {
        // We can ignore trailing newline
        if (!trie_contains(&trie, line)) {
            count++;
        }
    }
    gettimeofday(&lookup_end, DST_NONE);
    size_t lookup_diff = (lookup_end.tv_sec - lookup_start.tv_sec) * 1000000 + lookup_end.tv_usec -
                         lookup_start.tv_usec;
    size_t insertion_diff = (lookup_end.tv_sec - lookup_start.tv_sec) * 1000000 +
                            lookup_end.tv_usec - insertion_start.tv_usec;
    printf("%ld,%lu,%lu,%lu\n", lookup_diff, count, total, insertion_diff);
    // I should free the memory from the trie... 
     
}
