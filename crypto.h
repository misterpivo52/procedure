#ifndef CRYPTO_H
#define CRYPTO_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define KEY_SIZE 16

void init();
void sign(const uint8_t *hash, uint8_t *mac);
bool check_sign(const uint8_t *hash, const uint8_t *mac);

extern uint8_t secret[KEY_SIZE];

#endif
