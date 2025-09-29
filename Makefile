CC = gcc
CFLAGS = -Wall -g

all: task1 task2 additional

task1: task1.c
	$(CC) $(CFLAGS) -o task1 task1.c

task2: task2.c
	$(CC) $(CFLAGS) -o task2 task2.c

additional: additional.c
	$(CC) $(CFLAGS) -o additional additional.c

clean:
	rm -f task1 task2 additional

.PHONY: all clean