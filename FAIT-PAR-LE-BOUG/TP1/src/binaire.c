#include <stdio.h>

// Méthode simplifiée pour afficher un nombre en binaire
void printBinaryFast(int n) {
    // Afficher le nombre en binaire sur 32 bits
    for (int i = 31; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
    }
    printf("\n");
}

// Méthode demandée par l'exercice
void printBinaryExercice(int n) {
    int bits[32]; // Tableau pour stocker les bits (32 bits pour un entier)
    int i = 0;

    // Gérer le cas où n est nul
    if (n == 0) {
        printf("0\n");
        return;
    }

    // Rajouter les bits dans le tableau
    while (n > 0) {
        bits[i] = n % 2;
        n = n / 2;
        i++;
    }

    // Afficher les bits en ordre inverse car on a rempli le tableau à l'envers (du bit de poids faible au bit de poids fort)
    for (int j = i - 1; j >= 0; j--) {
        printf("%d", bits[j]);
    }

    printf("\n");
}

int main() {
    int nombre;

    printf("Entrez un nombre entier : ");
    scanf("%d", &nombre);

    printf("Affichage du nombre en binaire (méthode de l'exercice) : ");
    printBinaryExercice(nombre);

    printf("Affichage du nombre en binaire (méthode simplifiée) : ");
    printBinaryFast(nombre);

    return 0;
}
