#!/usr/bin/env bash

set -eux

mkdir -p results

curl -o data/hp-1.txt "https://raw.githubusercontent.com/amephraim/nlp/master/texts/J.%20K.%20Rowling%20-%20Harry%20Potter%201%20-%20Sorcerer's%20Stone.txt"
curl -o data/hp-2.txt "https://raw.githubusercontent.com/amephraim/nlp/master/texts/J.%20K.%20Rowling%20-%20Harry%20Potter%202%20-%20The%20Chamber%20Of%20Secrets.txt"
curl -o data/hp-3.txt "https://raw.githubusercontent.com/amephraim/nlp/master/texts/J.%20K.%20Rowling%20-%20Harry%20Potter%203%20-%20Prisoner%20of%20Azkaban.txt"
curl -o data/hp-4.txt "https://raw.githubusercontent.com/amephraim/nlp/master/texts/J.%20K.%20Rowling%20-%20Harry%20Potter%204%20-%20The%20Goblet%20of%20Fire.txt"

cd data
make
cd ..

curl -o data/words_alpha.txt "https://raw.githubusercontent.com/dwyl/english-words/master/words_alpha.txt"

