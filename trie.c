#include "trie.h"

#include <memory.h>
#include <stdbool.h>
#include <stdlib.h>

void trie_init(struct trie* trie) { memset(trie, 0, sizeof(*trie)); }

int trie_add(struct trie* trie, char* str) {
    if (*str == '\0' || *str == '\n' || *str == '\r') {
        trie->end = true;
        return 0;
    }
    if (*str < 'a' || *str > 'z') {
        return 1;
    }

    unsigned char i = *str - 'a';
    if (trie->next[i] == NULL) {
        trie->next[i] = malloc(sizeof(struct trie));
        trie_init(trie->next[i]);
    }
    return trie_add(trie->next[i], str + 1);
}

bool trie_contains(struct trie* trie, char* str) {
    if (*str == '\0' || *str == '\n' || *str == '\r') {
        return trie->end;
    }
    if (*str < 'a' || *str > 'z') {
        return false;
    }
    unsigned char i = *str - 'a';
    if (trie->next[i] == NULL) {
        return false;
    }
    return trie_contains(trie->next[i], str + 1);
}

/**
 * or not
 */
void trie_free(struct trie* trie) {
    for (size_t i = 0; i < ALPHA_LENGTH; i++) {
    }
}
