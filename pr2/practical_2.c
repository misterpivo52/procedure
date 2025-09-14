#include <stdio.h>
#include <string.h>

int get_bit(int num, int bit) 
{
    int mask = (1 << bit);
    return (num & mask) != 0;
}

int set_bit(int num, int bit)
{
    int mask = (1 << bit);
    return num | mask;
}

int clean_bit(int num, int bit)
{
    int mask = ~(1 << bit);
    return num & mask;
}

int main() 
{
    float float_num = 185.125f;
    printf("Original value = %f\n", float_num);

    unsigned int float_bits;
    memcpy(&float_bits, &float_num, sizeof(float_bits));

    for (int i = 0; i < 23; ++i) {
        float_bits = clean_bit(float_bits, i);
    }

    unsigned int mantissa_mask = 0x007FFFFF;
    unsigned int float_bits2;
    memcpy(&float_bits2, &float_num, sizeof(float_bits2));
    float_bits2 = float_bits2 & (~mantissa_mask);

    float cleaned_mantissa;
    memcpy(&cleaned_mantissa, &float_bits, sizeof(cleaned_mantissa));

    printf("Value with cleaned mantissa = %f\n", cleaned_mantissa);

    return 0;
}