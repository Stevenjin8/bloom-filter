#!/usr/bin/env bash

set -eux
set -o pipefail

SPEED_BF_FILE="results/bf-speed"
FILTER_BF_FILE="results/bf-filter"
SPEED_CC_FILE="results/cc-speed"
FILTER_CC_FILE="results/cc-filter"
SPEED_TRIE_FILE="results/trie-speed"
FILTER_TRIE_FILE="results/trie-filter"

HP_TOKENIZED="./data/hp-tokenized"
HP_UNIQUE="./data/hp-tokenized-unique"

DICTIONARY="./words_alpha.txt"

MAX_K=10

N_TRIALS=5

true > "$SPEED_BF_FILE"
true > "$FILTER_BF_FILE"
true > "$SPEED_CC_FILE"
true > "$FILTER_CC_FILE"
true > "$SPEED_TRIE_FILE"

for i in {1..8}
do
    ./main-bf "$DICTIONARY" "$i" < "$HP_TOKENIZED" >> /dev/null
    for j in $(seq 1 $N_TRIALS)
    do
        ./main-bf "$DICTIONARY" "$i" < "$HP_TOKENIZED" >> "$SPEED_BF_FILE"
    done
    ./main-bf "$DICTIONARY" "$i" < "$HP_UNIQUE" >> "$FILTER_BF_FILE"
done

CC_N_BINS=17  # log_2
for i in {1..11}
do
    ./main-cc "$DICTIONARY" "$i" "$CC_N_BINS" < "$HP_TOKENIZED" >> /dev/null
    for j in $(seq 1 $N_TRIALS)
    do
        ./main-cc "$DICTIONARY" "$i" "$CC_N_BINS" < "$HP_TOKENIZED" >> "$SPEED_CC_FILE"
    done
    ./main-cc "$DICTIONARY" "$i" "$CC_N_BINS" < "$HP_UNIQUE" >> "$FILTER_CC_FILE"
done

./main-trie "$DICTIONARY" < "$HP_TOKENIZED" >> "$SPEED_TRIE_FILE" >> /dev/null
for j in $(seq 1 $N_TRIALS)
do
    ./main-trie "$DICTIONARY" < "$HP_TOKENIZED" >> "$SPEED_TRIE_FILE"
done
./main-trie "$DICTIONARY" < "$HP_UNIQUE" > "$FILTER_TRIE_FILE"
