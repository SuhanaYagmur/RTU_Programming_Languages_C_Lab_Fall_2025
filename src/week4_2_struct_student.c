/*
 * week4_2_struct_student.c
 * Author: yagmur tugran
 * Student ID: 231ADB263
 * Description:
 *   Demonstrates defining and using a struct in C.
 *   Students should define a 'Student' struct with fields like name, id, and grade.
 *   Then create a few instances and print them.
 */

#include <stdio.h>
#include <string.h>

struct Student {
    char  name[50];
    int   id;
    float grade;
};

static void print_student(const struct Student *s) {
    printf("Öğrenci: %-20s  ID: %-6d  Not: %.1f\n", s->name, s->id, s->grade);
}

int main(void) {
    struct Student s1, s2, s3;

    
    snprintf(s1.name, sizeof s1.name, "Kubra Inanc");
    s1.id = 1001;  s1.grade = 9.1f;

    snprintf(s2.name, sizeof s2.name, "Yagmur Bolukbasi");
    s2.id = 1002;  s2.grade = 8.7f;

    snprintf(s3.name, sizeof s3.name, "Ximena Hawith");
    s3.id = 1003;  s3.grade = 9.5f;


    print_student(&s1);
    print_student(&s2);
    print_student(&s3);

    return 0;
}