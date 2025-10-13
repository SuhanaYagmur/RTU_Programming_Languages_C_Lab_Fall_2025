/*
 * Lab 3, Task 2
 * Student: Yagmur Tugran
 * ID: 231ADB263
 *
 * Pointers in function parameters:
 *  - swap(int *x, int *y): swap values of x and y
 *  - modify_value(int *x): multiply *x by 2
 */

#include <stdio.h>

/* Prototypes */
void swap(int *x, int *y);
void modify_value(int *x);

/* Implementations */
void swap(int *x, int *y) {
    int t = *x;
    *x = *y;
    *y = t;
}

void modify_value(int *x) {
    *x = (*x) * 2;
}

/* Simple tests */
int main(void) {
    int a = 3, b = 7;

    printf("Before swap: a=%d, b=%d\n", a, b);
    swap(&a, &b);
    printf("After  swap: a=%d, b=%d\n", a, b);

    modify_value(&a);
    printf("After modify_value: a=%d\n", a);

    return 0;
}
