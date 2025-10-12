#include <stdio.h>

int sum_to_n(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    return sum;
}

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        printf("Input error.\n");
        return 1;
    }

    if (n < 1) {
        printf("Error: n must be >= 1\n");
        return 1;
    }

    int result = sum_to_n(n);
    printf("Sum 1..%d = %d\n", n, result);
    return 0;
}
