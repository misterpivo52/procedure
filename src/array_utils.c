#include "array_utils.h"

int binary_search_recursive(const int arr[], int left, int right, int target) {
    if (left > right) {
        return -1;
    }

    int mid = left + (right - left) / 2;

    if (arr[mid] == target) {
        return mid;
    } else if (arr[mid] > target) {
        return binary_search_recursive(arr, left, mid - 1, target);
    } else {
        return binary_search_recursive(arr, mid + 1, right, target);
    }
}

int binary_search(const int arr[], int size, int target) {
    return binary_search_recursive(arr, 0, size - 1, target);
}