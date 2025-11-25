/*
 * Nom du fichier : volume.c
 * Objectif : Fonction pour calculer le volume d'une sphère.
 * Auteurs : Adrian RABIAN, Quentin BASTOS
 * Lignes importantes : 5, 6
 * Commande pour exécuter le fichier : gcc main.c surface.c volume.c -o sphere -lm && ./sphere
 */
#include <math.h>
#include "sphere.h"

// Fonction pour calculer le volume d'une sphère
float calculer_volume(float rayon) {
    return (4.0 / 3.0) * M_PI * pow(rayon, 3);
}
