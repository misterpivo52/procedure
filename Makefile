CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -std=c11 -g
CXXFLAGS = -Wall -Wextra -std=c++17 -g
LDFLAGS = -lgtest -lgtest_main -lpthread

all: test_c_list

c_list.o: c_list.c c_list.h
	$(CC) $(CFLAGS) -c c_list.c

test_c_list.o: test_c_list.cpp c_list.h
	$(CXX) $(CXXFLAGS) -c test_c_list.cpp

test_c_list: c_list.o test_c_list.o
	$(CXX) c_list.o test_c_list.o -o test_c_list $(LDFLAGS)

clean:
	rm -f *.o test_c_list test.txt

.PHONY: all clean