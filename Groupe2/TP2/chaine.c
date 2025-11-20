#include <stdio.h>
#include <string.h>

#define MAX_LEN 256

static void chomp(char *s) { char *p = strchr(s, '\n'); if (p) *p = '\0'; }

int main(void) {
    char s1[MAX_LEN], s2[MAX_LEN], copy[MAX_LEN], concat[2 * MAX_LEN];

    fputs("First string:\n", stdout);
    if (!fgets(s1, sizeof s1, stdin)) return 1;
    chomp(s1);

    fputs("Second string:\n", stdout);
    if (!fgets(s2, sizeof s2, stdin)) return 1;
    chomp(s2);

    printf("Length1=%zu Length2=%zu\n", strlen(s1), strlen(s2));

    strcpy(copy, s1);
    printf("Copy=\"%s\"\n", copy);

    strcpy(concat, s1);
    strcat(concat, s2);
    printf("Concat=\"%s\"\n", concat);

    return 0;
}
