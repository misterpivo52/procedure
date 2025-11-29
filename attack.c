#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "crypto.h"


long measure(const uint8_t *hash, const uint8_t *mac) {
    struct timespec t1, t2;
    clock_gettime(CLOCK_MONOTONIC, &t1);
    check_sign(hash, mac);
    clock_gettime(CLOCK_MONOTONIC, &t2);
    return (t2.tv_sec - t1.tv_sec) * 1000000000L +
           (t2.tv_nsec - t1.tv_nsec);
}

uint8_t recover_byte(uint8_t *guess, const uint8_t *hash, int pos) {
    long best = -1;
    uint8_t best_b = 0;

    for (int b = 0; b < 256; b++) {
        guess[pos] = b;
        long sum = 0;
        for (int i = 0; i < 200; i++)
            sum += measure(hash, guess);
        if (sum > best) {
            best = sum;
            best_b = b;
        }
    }
    return best_b;
}

int main() {
    init();

    uint8_t hash[KEY_SIZE];
    uint8_t mac[KEY_SIZE];
    uint8_t rec[KEY_SIZE];
    uint8_t guess[KEY_SIZE] = {0};

    for (int i = 0; i < KEY_SIZE; i++)
        hash[i] = random() % 256;

    printf("Hash: ");
    for (int i = 0; i < KEY_SIZE; i++)
        printf("%02x ", hash[i]);
    printf("\n");

    sign(hash, mac);

    printf("MAC: ");
    for (int i = 0; i < KEY_SIZE; i++)
        printf("%02x ", mac[i]);
    printf("\n");

    for (int i = 0; i < KEY_SIZE; i++) {
        rec[i] = recover_byte(guess, hash, i);
        guess[i] = rec[i];
        printf("Recovered byte %d: %02x\n", i, rec[i]);
    }

    printf("Recovered MAC: ");
    for (int i = 0; i < KEY_SIZE; i++)
        printf("%02x ", rec[i]);
    printf("\n");

    printf("Recovered secret: ");
    for (int i = 0; i < KEY_SIZE; i++)
        printf("%02x ", secret[i]);
    printf("\n");
}
