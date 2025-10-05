#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

/**
 * @brief Performs binary search on a sorted array to find the target value.
 *
 * This function searches for the specified target value within a sorted array of integers.
 * The array must be sorted in ascending order for binary search to work correctly.
 *
 * @param arr Pointer to the first element of the sorted integer array.
 * @param size Number of elements in the array.
 * @param target The value to search for in the array.
 * @return An index of the target value if found; otherwise, returns -1.
 *         Note: If the array contains duplicate values, any index containing
 *         the target value may be returned (not necessarily the first occurrence).
 */
int binary_search(const int arr[], int size, int target);

#endif // ARRAY_UTILS_H