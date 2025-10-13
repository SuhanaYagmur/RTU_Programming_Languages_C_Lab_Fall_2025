/*
 * Lab 3, Task 1
 * Student: Yagmur Tugran
 * ID: 231ADB263
 *
 * Implement array algorithms:
 *   - find minimum value
 *   - find maximum value
 *   - calculate sum
 *   - calculate average
 */

#include <stdio.h>
#include <limits.h>

/* Function prototypes */
int array_min(int arr[], int size);
int array_max(int arr[], int size);
int array_sum(int arr[], int size);
float array_avg(int arr[], int size);

int main(void) {
    int arr[] = {10, 20, 5, 30, 15};
    int size = (int)(sizeof(arr) / sizeof(arr[0]));

    printf("Min: %d\n", array_min(arr, size));      // 5
    printf("Max: %d\n", array_max(arr, size));      // 30
    printf("Sum: %d\n", array_sum(arr, size));      // 80
    printf("Avg: %.2f\n", array_avg(arr, size));    // 16.00

    return 0;
}

/* Implementations */
int array_min(int arr[], int size) {
    int m = INT_MAX;
    for (int i = 0; i < size; i++) {
        if (arr[i] < m) m = arr[i];
    }
    return m;
}

int array_max(int arr[], int size) {
    int m = INT_MIN;
    for (int i = 0; i < size; i++) {
        if (arr[i] > m) m = arr[i];
    }
    return m;
}

int array_sum(int arr[], int size) {
    int s = 0;
    for (int i = 0; i < size; i++) {
        s += arr[i];
    }
    return s;
}

float array_avg(int arr[], int size) {
    return (float)array_sum(arr, size) / (float)size;
}
