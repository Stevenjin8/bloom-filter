CC=cc
CFLAGS=-g -Wall -Wpedantic

default: main-bf main-trie

bf.o: bf.c
	$(CC) $(CFLAGS) -c bf.c -o bf.o

trie.o: trie.c
	$(CC) $(CFLAGS) -c trie.c -o trie.o

main-bf: main-bf.c bf.o
	$(CC) $(CFLAGS) bf.o main-bf.c -o main-bf

main-trie: main-trie.c trie.o
	$(CC) $(CFLAGS) trie.o main-trie.c -o main-trie

.PHONY: clean

clean:
	rm -rf main *.o
