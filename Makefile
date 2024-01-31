CC=cc
CFLAGS=-g -Wall -Wextra -pedantic -O3
OBJS=bf.o trie.o cc.o hash.o

default: main-bf main-trie main-cc

%.o: %.c 
	$(CC) $(CFLAGS) -c $^

main-cc: main-cc.c $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) main-cc.c -o main-cc

main-bf: main-bf.c $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) main-bf.c -o main-bf

main-trie: main-trie.c $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) main-trie.c -o main-trie

.PHONY: clean run fig setup

clean:
	rm -rf main-trie main-bf main-cc $(OBJS) fig/*.png *.dSYM

run: default
	./run.sh

setup: 
	./setup.sh

fig: main-trie main-bf make_graphs.py
	mkdir -p fig
	python make_graphs.py
