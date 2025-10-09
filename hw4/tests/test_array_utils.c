#include "array_utils.h"
#include <assert.h>
#include <stdio.h>

void test_rotate() {
    int arr[100][100] = {{0, 1, 2, 3}, {10, 11, 12, 13}, {20, 21, 22, 23}, {30, 31, 32, 33}};
    int n = 4;

    rotate_array_90(arr, n);

    assert(arr[0][0] == 30);
    assert(arr[0][1] == 20);
    assert(arr[0][2] == 10);
    assert(arr[0][3] == 0);
    assert(arr[3][3] == 3);

    printf("Test rotate passed!\n");
}

void test_checksum() {
    int arr[100][100] = {{1, 2}, {3, 4}};
    int n = 2;

    int sum = calculate_checksum(arr, n);
    assert(sum == 10);

    printf("Test checksum passed!\n");
}

int main() {
    test_rotate();
    test_checksum();
    printf("All array_utils tests passed!\n");
    return 0;
}