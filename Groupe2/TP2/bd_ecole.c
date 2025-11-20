#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STUDENTS 5
#define NOTES_COUNT 3
#define NAME_LEN 50
#define ADDR_LEN 100
#define BUF_LEN 256

typedef struct {
    char nom[NAME_LEN];
    char prenom[NAME_LEN];
    char adresse[ADDR_LEN];
    float notes[NOTES_COUNT];
} Student;

static void chomp(char *s) {
    char *p = strchr(s, '\n');
    if (p) *p = '\0';
}

int main(void) {
    Student db[STUDENTS];
    char buf[BUF_LEN];

    for (int i = 0; i < STUDENTS; i++) {
        printf("Student %d/%d\n", i + 1, STUDENTS);

        printf("  Nom: ");
        if (!fgets(buf, sizeof buf, stdin)) return 1;
        chomp(buf);
        strcpy(db[i].nom, buf); /* demonstration of strcpy */

        printf("  Prénom: ");
        if (!fgets(buf, sizeof buf, stdin)) return 1;
        chomp(buf);
        strcpy(db[i].prenom, buf);

        printf("  Adresse: ");
        if (!fgets(buf, sizeof buf, stdin)) return 1;
        chomp(buf);
        strcpy(db[i].adresse, buf);

        for (int j = 0; j < NOTES_COUNT; j++) {
            printf("  Note %d: ", j + 1);
            if (!fgets(buf, sizeof buf, stdin)) return 1;
            chomp(buf);
            float v = 0.0f;
            if (sscanf(buf, "%f", &v) != 1) v = 0.0f;
            db[i].notes[j] = v;
        }
        puts("");
    }

    puts("=== Stored students ===");
    for (int i = 0; i < STUDENTS; i++) {
        printf("Student %d:\n", i + 1);
        printf("  Nom: %s\n", db[i].nom);
        printf("  Prénom: %s\n", db[i].prenom);
        printf("  Adresse: %s\n", db[i].adresse);
        printf("  Notes:");
        for (int j = 0; j < NOTES_COUNT; j++) printf(" %.2f", db[i].notes[j]);
        printf("\n\n");
    }

    return 0;
}
