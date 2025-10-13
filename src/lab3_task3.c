/*
 * Lab 3, Task 3
 * Student: Yagmur Tugran
 * ID: 231ADB263
 *
 * Implement basic string handling functions WITHOUT <string.h>.
 *  - my_strlen  : return length (not counting '\0')
 *  - my_strcpy  : copy src into dest and add trailing '\0'
 */

#include <stdio.h>

/* Function prototypes */
int my_strlen(const char *str);
void my_strcpy(char *dest, const char *src);

/* Implementations */
int my_strlen(const char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

void my_strcpy(char *dest, const char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0'; /* null terminator */
}

/* Simple tests */
int main(void) {
    char test[] = "Programming in C";
    char copy[100];

    int len = my_strlen(test);
    printf("Length: %d\n", len);

    my_strcpy(copy, test);
    printf("Copy: %s\n", copy);

    return 0;
}
