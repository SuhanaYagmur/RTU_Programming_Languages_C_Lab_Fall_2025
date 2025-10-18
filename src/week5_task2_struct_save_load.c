/* Week 5 - Task 2 | Student: Yagmur Tugran | ID: 231ADB263 */
#include <stdio.h>

typedef struct {
    char  name[50];
    int   age;
    float gpa;
} Student;

int save_student(const char *path, const Student *s) {
    FILE *f = fopen(path, "w");
    if (f == NULL) return 0;
    fprintf(f, "%s %d %.2f\n", s->name, s->age, s->gpa);
    fclose(f);
    return 1;
}

int load_student(const char *path, Student *s) {
    FILE *f = fopen(path, "r");
    if (f == NULL) return 0;
    if (fscanf(f, "%49s %d %f", s->name, &s->age, &s->gpa) != 3) {
        fclose(f);
        return 0;
    }
    fclose(f);
    return 1;
}

int main(void) {
    const char *file = "student.txt";
    Student a = { "Yagmur", 20, 3.90f };
    Student b = { "", 0, 0.0f };

    printf("save...\n");
    if (!save_student(file, &a)) {
        printf("save failed\n");
        return 1;
    }

    printf("load...\n");
    if (!load_student(file, &b)) {
        printf("load failed\n");
        return 1;
    }

    printf("loaded: %s, %d, GPA %.2f\n", b.name, b.age, b.gpa);
    return 0;
}
