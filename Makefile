CC = gcc
CFLAGS = -Wall -g

all: anagram matrix

anagram: anagram.c
	$(CC) $(CFLAGS) -o anagram anagram.c

matrix: matrix.c
	$(CC) $(CFLAGS) -o matrix matrix.c

clean:
	rm -f anagram matrix main

.PHONY: all clean