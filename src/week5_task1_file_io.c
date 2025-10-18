/* Week 5 - Task 1 | Student: Yagmur Tugran | ID: 231ADB263 */
#include <stdio.h>

int main(void) {
    const char *fname = "data.txt";
    FILE *fp;
    char line[256];

    fp = fopen(fname, "w");
    if (fp == NULL) {
        printf("dosya acilamadi (yaz): %s\n", fname);
        return 1;
    }
    fprintf(fp, "Hello, file I/O in C!\n");
    fprintf(fp, "This is another line.\n");
    fprintf(fp, "End of demo.\n");
    fclose(fp);
    printf("Finished writing -> %s\n", fname);

    fp = fopen(fname, "r");
    if (fp == NULL) {
        printf("dosya acilamadi (oku): %s\n", fname);
        return 1;
    }
    printf("Contents:\n");
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }
    fclose(fp);
    return 0;
}
