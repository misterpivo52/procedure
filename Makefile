CC = gcc

CFLAGS = -Wall -Wextra -std=c99

XOR_TARGET = xor_cipher
FLOAT_TARGET = float_representation

XOR_SRC = xor_cipher.c
FLOAT_SRC = float_representation.c

all: $(XOR_TARGET) $(FLOAT_TARGET)

$(XOR_TARGET): $(XOR_SRC)
	$(CC) $(CFLAGS) -o $(XOR_TARGET) $(XOR_SRC)

xor_cipher: $(XOR_TARGET)

$(FLOAT_TARGET): $(FLOAT_SRC)
	$(CC) $(CFLAGS) -o $(FLOAT_TARGET) $(FLOAT_SRC)

float_representation: $(FLOAT_TARGET)

clean: clean_xor_cipher clean_float_representation

clean_xor_cipher:
	rm -f $(XOR_TARGET)

clean_float_representation:
	rm -f $(FLOAT_TARGET)

.PHONY: all xor_cipher float_representation clean clean_xor_cipher clean_float_representation