#include <stdio.h>

int main() {
    int X, Y;
    int xor_result;
    int count = 0;
    int i;

    printf("Enter first number (X): ");
    scanf("%d", &X);

    printf("Enter second number (Y): ");
    scanf("%d", &Y);
    printf("X = %d, binary: ", X);
    for (i = 31; i >= 0; i--) {
        if ((X >> i) & 1) {
            printf("1");
        } else {
            printf("0");
        }
        if (i > 0 && i % 4 == 0) printf(" ");
    }
    printf("\n");

    printf("Y = %d, binary: ", Y);
    for (i = 31; i >= 0; i--) {
        if ((Y >> i) & 1) {
            printf("1");
        } else {
            printf("0");
        }
        if (i > 0 && i % 4 == 0) printf(" ");
    }
    printf("\n");

    xor_result = X ^ Y;

    printf("XOR result: ");
    for (i = 31; i >= 0; i--) {
        if ((xor_result >> i) & 1) {
            printf("1");
        } else {
            printf("0");
        }
        if (i > 0 && i % 4 == 0) printf(" ");
    }
    printf("\n");

    while (xor_result != 0) {
        if (xor_result & 1) {
            count++;
        }
        xor_result = xor_result >> 1;
    }

    printf("Number of bits to change: %d\n", count);

    return 0;
}