#! /usr/local/bin/bash

set -eux
set -o pipefail

SPEED_BF_FILE="results/bf-speed"
FILTER_BF_FILE="results/bf-filter"
SPEED_TRIE_FILE="results/trie-speed"
FILTER_TRIE_FILE="results/trie-filter"

HP_TOKENIZED="./data/hp-tokenized"
HP_UNIQUE="./data/hp-tokenized-unique"

DICTIONARY="./words_alpha.txt"

MAX_K=10

N_TRIALS=5

true > "$SPEED_BF_FILE"
true > "$FILTER_BF_FILE"
true > "$SPEED_TRIE_FILE"

for i in {1..10}
do
    ./main-bf "$DICTIONARY" "$i" < "$HP_TOKENIZED" >> /dev/null
    for j in $(seq 1 $N_TRIALS)
    do
        ./main-bf "$DICTIONARY" "$i" < "$HP_TOKENIZED" >> "$SPEED_BF_FILE"
    done
    ./main-bf "$DICTIONARY" "$i" < "$HP_UNIQUE" >> "$FILTER_BF_FILE"
done

./main-trie "$DICTIONARY" < "$HP_TOKENIZED" >> "$SPEED_TRIE_FILE" >> /dev/null
for j in $(seq 1 $N_TRIALS)
do
    ./main-trie "$DICTIONARY" < "$HP_TOKENIZED" >> "$SPEED_TRIE_FILE"
done
./main-trie "$DICTIONARY" < "$HP_UNIQUE" > "$FILTER_TRIE_FILE"
