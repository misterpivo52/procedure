#include <stdio.h>

void print_binary(int num) {
    for (int i = 31; i >= 0; i--) {
        if (num & (1 << i)) {
            printf("1");
        } else {
            printf("0");
        }
    }
}

int main() {
    int value, key;
    int encrypted, decrypted;

    printf("Enter a value: ");
    scanf("%d", &value);

    printf("Enter a key (number of bits for XOR): ");
    scanf("%d", &key);

    printf("Original value (Decimal): %d\n", value);
    printf("Binary: ");
    print_binary(value);
    printf("\n");

    encrypted = value ^ key;
    printf("Encrypted value (Decimal): %d\n", encrypted);
    printf("Binary: ");
    print_binary(encrypted);
    printf("\n");

    decrypted = encrypted ^ key;
    printf("Decrypted value (Original): %d\n", decrypted);
    printf("Binary: ");
    print_binary(decrypted);
    printf("\n");

    return 0;
}