CC = gcc
CFLAGS = -Wall -std=c11

all:
	$(CC) $(CFLAGS) main.c src/list.c -o main.exe
	$(CC) $(CFLAGS) tests/test_list.c src/list.c -o test.exe
	$(CC) $(CFLAGS) task2_main.c src/array_utils.c -o task2.exe
	$(CC) $(CFLAGS) leetcode.c -o leetcode.exe

run:
	main.exe

test:
	test.exe

task2:
	task2.exe

leetcode:
	leetcode.exe

clean:
	rm -f *.exe