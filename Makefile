CC=cc
CFLAGS=-g -Wall -Wpedantic -O2

default: main-bf main-trie

bf.o: bf.c bf.h
	$(CC) $(CFLAGS) -c bf.c -o bf.o

trie.o: trie.c trie.h
	$(CC) $(CFLAGS) -c trie.c -o trie.o

main-bf: main-bf.c bf.o
	$(CC) $(CFLAGS) bf.o main-bf.c -o main-bf

main-trie: main-trie.c trie.o
	$(CC) $(CFLAGS) trie.o main-trie.c -o main-trie

.PHONY: clean run

clean:
	rm -rf main-trie main-bf *.o

run: default
	./run.sh
