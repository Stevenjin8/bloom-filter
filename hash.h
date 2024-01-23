#ifndef __HASH_H 
#define __HASH_H

#include <stdlib.h>

/**
 * str: the string to hash
 * h:   initial seed value
 *
 * stops at end of string or newline.
 *
 * https://stackoverflow.com/questions/2351087/what-is-the-best-32bit-hash-function-for-short-strings-tag-names
 */
size_t hash(char *str, size_t h);
size_t hash2(char *str, size_t h);

size_t hash_n(size_t n);

#endif
