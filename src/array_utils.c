#include "array_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void process_2d_array(void) {
    int N;
    printf("Enter the size of the array (N): ");
    scanf("%d", &N);

    int arr[N][N];

    srand(time(NULL));

    int* ptr = (int*)arr;
    for (int i = 0; i < N * N; i++) {
        *(ptr + i) = rand() % 11;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", *((int*)arr + i * N + j));
        }
        printf("\n");
    }

    int main_sum = 0;
    for (int i = 0; i < N; i++) {
        main_sum += *((int*)arr + i * N + i);
    }

    int secondary_sum = 0;
    for (int i = 0; i < N; i++) {
        secondary_sum += *((int*)arr + i * N + (N - 1 - i));
    }

    printf("Sum of the main diagonal: %d\n", main_sum);
    printf("Sum of the second diagonal: %d\n", secondary_sum);
}