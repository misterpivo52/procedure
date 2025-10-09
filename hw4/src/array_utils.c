#include "array_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void rotate_array_90(int arr[][100], int n) {
    int temp[100][100];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            temp[j][n - 1 - i] = arr[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            arr[i][j] = temp[i][j];
        }
    }
}

void fill_random(int arr[][100], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            arr[i][j] = rand() % 100;
        }
    }
}

void print_array(int arr[][100], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int calculate_checksum(int arr[][100], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum += arr[i][j];
        }
    }
    return sum;
}