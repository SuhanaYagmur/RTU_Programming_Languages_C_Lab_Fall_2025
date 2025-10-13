/*
 * week4_3_struct_database.c
 * Author: yagmur tugran
 * Student ID: 231ADB263
 * Description:
 *   Simple in-memory "database" using an array of structs.
 *   Students will use malloc to allocate space for multiple Student records,
 *   then input, display, and possibly search the data.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char  name[50];
    int   id;
    float grade;
};

int main(void) {
    int n = 3; /* sabit öğrenci sayısı */
    struct Student *students = (struct Student *)malloc((size_t)n * sizeof *students);
    if (!students) {
        printf("Hata: malloc başarısız.\n");
        return 1;
    }

    
    snprintf(students[0].name, sizeof students[0].name, "Kubra Inanc");
    students[0].id = 1001;  students[0].grade = 9.1f;

    snprintf(students[1].name, sizeof students[1].name, "Yagmur Bolukbasi");
    students[1].id = 1002;  students[1].grade = 8.7f;

    snprintf(students[2].name, sizeof students[2].name, "Ximena Hawith");
    students[2].id = 1003;  students[2].grade = 9.5f;

    
    printf("\n%-6s %-20s %-5s\n", "ID", "Name", "Grade");
    for (int i = 0; i < n; i++) {
        printf("%-6d %-20s %.1f\n", students[i].id, students[i].name, students[i].grade);
    }

    free(students);
    return 0;
}

