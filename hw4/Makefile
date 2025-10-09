CC=gcc
CFLAGS=-Wall -Iinclude
SRC=src/bisection.c src/array_utils.c
TESTS=tests/test_bisection tests/test_array_utils

all: main tests

main: main.c $(SRC)
	$(CC) $(CFLAGS) main.c $(SRC) -lm -o main

tests: $(TESTS)

tests/test_bisection: tests/test_bisection.c $(SRC)
	$(CC) $(CFLAGS) tests/test_bisection.c $(SRC) -lm -o tests/test_bisection

tests/test_array_utils: tests/test_array_utils.c $(SRC)
	$(CC) $(CFLAGS) tests/test_array_utils.c $(SRC) -lm -o tests/test_array_utils

clean:
	rm -f main $(TESTS)
