CC = clang
CFLAGS = -std=c99 -O2

all: attack

attack: crypto.c crypto.c crypto.h
	$(CC) $(CFLAGS) attack.c crypto.c -o attack

clean:
	rm -f attack
