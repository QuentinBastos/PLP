/*
 * Nom du fichier : surface.c
 * Objectif : Fonction pour calculer la surface d'une sphère.
 * Auteurs : Adrian RABIAN, Quentin BASTOS
 * Lignes importantes : 5, 6
 * Commande pour exécuter le fichier : gcc main.c surface.c volume.c -o sphere -lm && ./sphere
 */
#include <math.h>
#include "sphere.h"

// Fonction pour calculer la surface d'une sphère
float calculer_surface(float rayon) {
    return 4 * M_PI * pow(rayon, 2);
}
