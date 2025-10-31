CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: program_list program_getline test_list test_getline

program_list: program_list.c list.c
	$(CC) $(CFLAGS) -o program_list program_list.c list.c

program_getline: program_getline.c getline.c
	$(CC) $(CFLAGS) -o program_getline program_getline.c getline.c

test_list: test_list.c list.c
	$(CC) $(CFLAGS) -o test_list test_list.c list.c

test_getline: test_getline.c getline.c
	$(CC) $(CFLAGS) -o test_getline test_getline.c getline.c

clean:
	rm -f program_list program_getline test_list test_getline test_input.txt

valgrind_program_list: program_list
	valgrind --leak-check=full ./program_list

valgrind_program_getline: program_getline
	valgrind --leak-check=full ./program_getline

valgrind_list: test_list
	valgrind --leak-check=full ./test_list

valgrind_getline: test_getline
	valgrind --leak-check=full ./test_getline