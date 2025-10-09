#include "bisection.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

void test_bisection_basic() {
    int iterations;
    double result = bisection_search(2.0, 3.0, -10.0, 10.0, 0.0001, &iterations);
    assert(fabs(result - (-3.0)) < 0.001);
    printf("Test 1 passed: result = %f, iterations = %d\n", result, iterations);
}

void test_bisection_zero_intersection() {
    int iterations;
    double result = bisection_search(1.0, 5.0, -10.0, 10.0, 0.0001, &iterations);
    assert(iterations > 0);
    printf("Test 2 passed: result = %f, iterations = %d\n", result, iterations);
}

void test_bisection_negative() {
    int iterations;
    double result = bisection_search(0.5, -2.0, -10.0, 10.0, 0.0001, &iterations);
    assert(fabs(result - (-4.0)) < 0.001);
    printf("Test 3 passed: result = %f, iterations = %d\n", result, iterations);
}

void test_bisection_positive() {
    int iterations;
    double result = bisection_search(3.0, 5.0, -10.0, 10.0, 0.0001, &iterations);
    assert(fabs(result - (-2.5)) < 0.001);
    printf("Test 4 passed: result = %f, iterations = %d\n", result, iterations);
}

int main() {
    test_bisection_basic();
    test_bisection_zero_intersection();
    test_bisection_negative();
    test_bisection_positive();
    printf("All bisection tests passed!\n");
    return 0;
}