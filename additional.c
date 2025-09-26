#include <stdio.h>

void print_bin(unsigned n) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
        if (i && i % 4 == 0) printf(" ");
    }
    printf("\n");
}

int main() {
    int X, Y;
    printf("Enter X: ");
    scanf("%d", &X);
    printf("Enter Y: ");
    scanf("%d", &Y);


    printf("X = %d, binary: ", X);  print_bin(X);
    printf("Y = %d, binary: ", Y);  print_bin(Y);

    int xor_result = X ^ Y, count = 0;
    printf("X ^ Y = %d, binary: ", xor_result);  print_bin(xor_result);

    while (xor_result) { count += xor_result & 1; xor_result >>= 1; }
    printf("Number of bits to change: %d\n", count);

    return 0;
}
