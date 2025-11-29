#include "crypto.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

uint8_t secret[KEY_SIZE];
uint64_t state = 0;

void init() {
    srandom(time(NULL));
    printf("Secret: ");
    for (int i = 0; i < KEY_SIZE; ++i) {
        secret[i] = random() % 256;
        printf("%02x ", secret[i]);
    }
    printf("\n");
}

void sign(const uint8_t *hash, uint8_t *mac) {
    for (int i = 0; i < KEY_SIZE; ++i)
        mac[i] = hash[i] ^ secret[i];
}

bool check_sign(const uint8_t *hash, const uint8_t *mac) {
    for (int i = 0; i < KEY_SIZE; ++i) {
        for (int j = 0; j < 1000; ++j)
            state *= random() ^ hash[i] ^ secret[i] ^ mac[i];
        if ((hash[i] ^ secret[i]) != mac[i])
            return false;
    }
    return true;
}
