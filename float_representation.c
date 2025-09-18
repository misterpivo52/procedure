#include <stdio.h>

union FloatBits {
    float f;
    unsigned int bits;
};

int main() {
    float number;
    union FloatBits fb;

    printf("Enter a floating-point number: ");
    scanf("%f", &number);

    fb.f = number;

    unsigned int sign_bit = (fb.bits >> 31) & 1;
    unsigned int exponent_bits = (fb.bits >> 23) & 0xFF;
    unsigned int mantissa_bits = fb.bits & 0x7FFFFF;

    printf("Sign bit: %s\n", sign_bit ? "-" : "+");

    int real_exponent = exponent_bits - 127;
    printf("Exponent value: %d\n", real_exponent);

    double mantissa_value = 0.0;
    for (int i = 0; i < 23; i++) {
        if (mantissa_bits & (1 << (22 - i))) {
            mantissa_value += 1.0 / (1 << (i + 1));
        }
    }
    printf("Mantissa value: %.5f\n", mantissa_value);

    double reconstructed = (sign_bit ? -1.0 : 1.0) * (1.0 + mantissa_value);

    if (real_exponent >= 0) {
        for (int i = 0; i < real_exponent; i++) {
            reconstructed *= 2.0;
        }
    } else {
        for (int i = 0; i < -real_exponent; i++) {
            reconstructed /= 2.0;
        }
    }

    printf("Reconstructed value: (1.0+%f) * 2**%d = %f\n",
           mantissa_value, real_exponent, reconstructed);

    return 0;
}