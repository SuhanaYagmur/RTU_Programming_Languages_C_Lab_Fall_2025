/*
 * week4_1_dynamic_array.c
 * Student: Yagmur Tugran
 * ID: 231ADB263
 * Description:
 *   Create a dynamic int array with malloc, read values, compute sum & average,
 *   print results, and free memory.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int n;
  int* arr = NULL;

  printf("Enter number of elements: ");
  if (scanf("%d", &n) != 1 || n <= 0) {
    printf("Invalid size.\n");
    return 1;
  }

  arr = (int*)malloc((size_t)n * sizeof(int));
  if (arr == NULL) {
    printf("Error: malloc failed.\n");
    return 1;
  }

  printf("Enter %d integers: ", n);
  for (int i = 0; i < n; i++) {
    if (scanf("%d", &arr[i]) != 1) {
      printf("Input error.\n");
      free(arr);
      return 1;
    }
  }

  long long sum = 0;
  for (int i = 0; i < n; i++) {
    sum += arr[i];
  }
  float avg = (float)sum / (float)n;

  printf("Sum = %lld\n", sum);
  printf("Average = %.2f\n", avg);

  free(arr);
  return 0;
}
