CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -L. -lc_list
LIB = c_list.dll
IMPLIB = libc_list.a
TARGETS = main.exe interactive.exe test.exe

.PHONY: all run-main run-interactive run-tests clean

all: $(TARGETS)

%.exe: %.o $(LIB)
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

c_list.o: c_list.c
	$(CC) $(CFLAGS) -fPIC -c c_list.c -o c_list.o

$(LIB): c_list.o
	$(CC) -shared -o $(LIB) c_list.o -Wl,--out-implib,$(IMPLIB)

run-main: main.exe
	./main.exe

run-interactive: interactive.exe
	./interactive.exe

run-tests: test.exe
	./test.exe

clean:
	$(RM) *.o *.a *.dll *.so $(TARGETS)
