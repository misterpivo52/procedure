CC=gcc
CFLAGS=-I.

all: main

main: main.o
	$(CC) -o main main.o

main.o: main.c
	$(CC) -c main.c

clean:
	rm -f *.o main