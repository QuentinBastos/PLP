#include <stdio.h>

int main() {
    int a = 16;
    int b = 3;

    // Opérations arithmétiques
    int addition = a + b;
    int soustraction = a - b;
    int multiplication = a * b;
    float division = (float)a / b;
    int modulo = a % b;

    // Opérations logiques
    int egal = (a == b);
    int superieur = (a > b);

    // Affichage des résultats
    printf("Addition: %d\n", addition);
    printf("Soustraction: %d\n", soustraction);
    printf("Multiplication: %d\n", multiplication);
    printf("Division: %.2f\n", division);
    printf("Modulo: %d\n", modulo);
    printf("a == b: %d\n", egal);
    printf("a > b: %d\n", superieur);

    return 0;
}
