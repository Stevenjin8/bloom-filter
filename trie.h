#ifndef __TRIE_H
#define __TRIE_H

#include <stdbool.h>
#include <stdlib.h>
#define ALPHA_LENGTH 26

struct trie {
    bool end;
    struct trie* next[ALPHA_LENGTH];
};

void trie_init(struct trie* trie);

int trie_add(struct trie* trie, char* str);

bool trie_contains(struct trie* trie, char* str);

#endif
