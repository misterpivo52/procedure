#include "bisection.h"
#include "array_utils.h"
#include <stdio.h>

int main() {
    printf("Task 1: Bisection Search\n");
    double a, b;
    printf("Enter coefficient a: ");
    scanf("%lf", &a);
    printf("Enter coefficient b: ");
    scanf("%lf", &b);

    int iterations;
    double result = bisection_search(a, b, -100.0, 100.0, 0.0001, &iterations);
    printf("Intersection point: x = %f\n", result);
    printf("Number of iterations: %d\n\n", iterations);

    printf("Task 2: Array Rotation\n");
    int n;
    printf("Enter array size N: ");
    scanf("%d", &n);

    int arr[100][100];
    fill_random(arr, n);

    printf("Original array:\n");
    print_array(arr, n);

    rotate_array_90(arr, n);

    printf("\nRotated array (90° clockwise):\n");
    print_array(arr, n);

    printf("\nTask 3: Checksum\n");
    int checksum = calculate_checksum(arr, n);
    printf("Checksum: %d\n", checksum);

    return 0;
}