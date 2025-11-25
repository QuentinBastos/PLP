/*
 * Nom du fichier : main.c
 * Objectif : Programme principal pour tester les fonctions de calcul de sphère.
 * Auteurs : Adrian RABIAN, Quentin BASTOS
 * Commande pour exécuter le fichier : gcc main.c surface.c volume.c -o sphere -lm && ./sphere
 */
#include <stdio.h>
#include "sphere.h"

int main() {
    float rayon = 5.0;
    float volume = calculer_volume(rayon);
    float surface = calculer_surface(rayon);

    printf("Le volume de la sphère de rayon %.2f est %.2f\n", rayon, volume);
    printf("La surface de la sphère de rayon %.2f est %.2f\n", rayon, surface);

    return 0;
}
