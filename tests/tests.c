#include <assert.h>
#include <limits.h>
#include "array_utils.h"
#include <stdio.h>

// Test 1: 0 elements in array
void test_empty_array() {
    printf("Test 1: Empty array... ");
    const int arr[] = {};
    assert(binary_search(arr, 0, 5) == -1);
    printf("PASSED\n");
}

// Test 2: Single element - found
void test_single_element_found() {
    printf("Test 2: Single element found... ");
    const int arr[] = {5};
    assert(binary_search(arr, 1, 5) == 0);
    printf("PASSED\n");
}

// Test 3: Single element - not found
void test_single_element_not_found() {
    printf("Test 3: Single element not found... ");
    const int arr[] = {5};
    assert(binary_search(arr, 1, 3) == -1);
    printf("PASSED\n");
}

// Test 4: Target at first position
void test_target_at_start() {
    printf("Test 4: Target at first position... ");
    const int arr[] = {1, 3, 5, 7, 9};
    assert(binary_search(arr, 5, 1) == 0);
    printf("PASSED\n");
}

// Test 5: Target at last position
void test_target_at_end() {
    printf("Test 5: Target at last position... ");
    const int arr[] = {1, 3, 5, 7, 9};
    assert(binary_search(arr, 5, 9) == 4);
    printf("PASSED\n");
}

// Test 6: Target in middle
void test_target_in_middle() {
    printf("Test 6: Target in middle... ");
    const int arr[] = {1, 3, 5, 7, 9};
    assert(binary_search(arr, 5, 5) == 2);
    printf("PASSED\n");
}

// Test 7: Target not in array (smaller than all)
void test_target_too_small() {
    printf("Test 7: Target smaller than all elements... ");
    const int arr[] = {5, 10, 15, 20};
    assert(binary_search(arr, 4, 3) == -1);
    printf("PASSED\n");
}

// Test 8: Target not in array (larger than all)
void test_target_too_large() {
    printf("Test 8: Target larger than all elements... ");
    const int arr[] = {5, 10, 15, 20};
    assert(binary_search(arr, 4, 25) == -1);
    printf("PASSED\n");
}

// Test 9: Target not in array (in range but not present)
void test_target_missing_in_range() {
    printf("Test 9: Target in range but missing... ");
    const int arr[] = {1, 3, 5, 7, 9};
    assert(binary_search(arr, 5, 6) == -1);
    printf("PASSED\n");
}

// Test 10: Large array
void test_large_array() {
    printf("Test 10: Large array... ");
    const int arr[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30};
    assert(binary_search(arr, 15, 18) == 8);
    assert(binary_search(arr, 15, 2) == 0);
    assert(binary_search(arr, 15, 30) == 14);
    printf("PASSED\n");
}

// Test 11: Array with negative numbers
void test_negative_numbers() {
    printf("Test 11: Array with negative numbers... ");
    const int arr[] = {-10, -5, 0, 5, 10};
    assert(binary_search(arr, 5, -5) == 1);
    assert(binary_search(arr, 5, 0) == 2);
    printf("PASSED\n");
}

// Test 12: Array with duplicates (returns first occurrence)
void test_duplicates() {
    printf("Test 12: Array with duplicates... ");
    const int arr[] = {1, 3, 5, 5, 5, 7, 9};
    int result = binary_search(arr, 7, 5);
    // Should return an index where arr[index] == 5
    assert(result >= 2 && result <= 4);
    assert(arr[result] == 5);
    printf("PASSED (found at index %d)\n", result);
}

int main() {
    printf("Running binary_search tests...\n");
    printf("================================\n");

    test_empty_array();
    test_single_element_found();
    test_single_element_not_found();
    test_target_at_start();
    test_target_at_end();
    test_target_in_middle();
    test_target_too_small();
    test_target_too_large();
    test_target_missing_in_range();
    test_large_array();
    test_negative_numbers();
    test_duplicates();

    printf("================================\n");
    printf("All tests passed!\n");
    return 0;
}