#include "trie.h"

#include <memory.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * Initialize trie
 */
void trie_init(struct trie* trie) { memset(trie, 0, sizeof(*trie)); }

/**
 * Add element to trie.
 * Returns -1 if insertion fails
 */
int trie_add(struct trie* trie, char* str) {
    int total = 0;
    if (*str == '\0' || *str == '\n' || *str == '\r') {
        trie->end = true;
        return 0;
    }
    // Trie can only contain lowercase alphabetic characters.
    if (*str < 'a' || *str > 'z') {
        return -1;
    }

    uint8_t i = *str - 'a';
    if (trie->next[i] == NULL) {
        trie->next[i] = malloc(sizeof(struct trie));
        if (trie->next[i] == NULL) {
            return -1;
        }
        total = total + sizeof(struct trie);
        trie_init(trie->next[i]);
    }
    return total + trie_add(trie->next[i], str + 1);
}

/**
 * Check containment
 */
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
