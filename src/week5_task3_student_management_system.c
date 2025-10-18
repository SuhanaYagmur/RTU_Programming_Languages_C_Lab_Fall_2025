/* Week 5 - Task 3 | Student: Yagmur Tugran | ID: 231ADB263 */
#include <stdio.h>

typedef struct {
    char  name[50];
    int   id;
    float gpa;
} Student;

#define MAX_STUDENTS 200

int load_students(const char *path, Student arr[], int max) {
    FILE *f = fopen(path, "r");
    if (!f) return 0;
    int n = 0;
    while (n < max && fscanf(f, "%49s %d %f", arr[n].name, &arr[n].id, &arr[n].gpa) == 3) {
        n++;
    }
    fclose(f);
    return n;
}

int save_students(const char *path, const Student arr[], int count) {
    FILE *f = fopen(path, "w");
    if (!f) return 0;
    for (int i = 0; i < count; i++) {
        fprintf(f, "%s %d %.2f\n", arr[i].name, arr[i].id, arr[i].gpa);
    }
    fclose(f);
    return 1;
}

void list_students(const Student arr[], int count) {
    if (count == 0) {
        printf("(no records)\n");
        return;
    }
    printf("ID    Name                 GPA\n");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %.2f\n", arr[i].id, arr[i].name, arr[i].gpa);
    }
}

void add_student(Student arr[], int *count, int max) {
    if (*count >= max) {
        printf("storage full\n");
        return;
    }
    Student s;
    printf("Enter name (no spaces): ");
    if (scanf("%49s", s.name) != 1) { printf("input error\n"); return; }
    printf("Enter ID: ");
    if (scanf("%d", &s.id) != 1)     { printf("input error\n"); return; }
    printf("Enter GPA: ");
    if (scanf("%f", &s.gpa) != 1)    { printf("input error\n"); return; }
    arr[*count] = s;
    (*count)++;
    printf("added\n");
}

int main(void) {
    const char *file = "students.txt";
    Student db[MAX_STUDENTS];
    int count = load_students(file, db, MAX_STUDENTS);

    for (;;) {
        int choice;
        printf("\n=== Student Management System ===\n");
        printf("1. List students\n");
        printf("2. Add student\n");
        printf("3. Save and Exit\n");
        printf("Select: ");
        if (scanf("%d", &choice) != 1) {
            printf("input error\n");
            return 1;
        }
        if (choice == 1) {
            list_students(db, count);
        } else if (choice == 2) {
            add_student(db, &count, MAX_STUDENTS);
        } else if (choice == 3) {
            if (!save_students(file, db, count)) {
                printf("save error\n");
                return 1;
            }
            printf("saved, bye\n");
            break;
        } else {
            printf("unknown option\n");
        }
    }
    return 0;
}
