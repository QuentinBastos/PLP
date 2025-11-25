#include <stdio.h>
#define PI 3.14159

int main() {
    float rayon;

    // Demande à l'utilisateur de saisir le rayon du cercle
    printf("Rayon du cercle (cm) : ");
    if (scanf("%f", &rayon) != 1) {
        printf("Erreur de lecture du rayon.\n");
        return 1;
    }

    // Calcul de l'aire et du périmètre du cercle
    const float aire = PI * rayon * rayon;
    const float perimeter = 2 * rayon * PI;

    // Affichage des résultats
    printf("L'aire du cercle : %f cm2\nLe périmètre du cercle : %f cm\n", aire, perimeter);
    return 0;
}
