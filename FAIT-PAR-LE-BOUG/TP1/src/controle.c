#include <stdio.h>

int main() {
    // Divisibilité par 4 mais pas par 6 (utilisation de for)
    printf("Nombres divisibles par 4 mais pas par 6 (for):\n");
    for (int i = 1; i <= 1000; i++) {
        if (i % 4 == 0 && i % 6 != 0) {
            printf("%d, ", i);
        }
    }

    // Nombres pairs et divisibles par 8 (utilisation de while)
    printf("\nNombres pairs et divisibles par 8 (while):\n");
    int i = 1;
    while (i <= 1000) {
        if (i % 2 == 0 && i % 8 == 0) {
            printf("%d, ", i);
        }
        i++;
    }

    // Divisibilité par 5 ou 7 mais pas par 10 (utilisation de do...while)
    printf("\nNombres divisibles par 5 ou 7 mais pas par 10 (do...while):\n");
    i = 1;
    do {
        if ((i % 5 == 0 || i % 7 == 0) && i % 10 != 0) {
            printf("%d, ", i);
        }
        i++;
    } while (i <= 1000);

    return 0;
}
