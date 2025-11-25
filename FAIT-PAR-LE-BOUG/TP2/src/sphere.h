/*
 * Nom du fichier : sphere.h
 * Objectif : Déclarations des fonctions pour le calcul de sphère.
 * Auteurs : Adrian RABIAN, Quentin BASTOS
 * Commande pour exécuter le fichier : gcc main.c surface.c volume.c -o sphere -lm && ./sphere
 */
#ifndef SPHERE_H
#define SPHERE_H

// Fonction pour calculer le volume d'une sphère
float calculer_volume(float rayon);

// Fonction pour calculer la surface d'une sphère
float calculer_surface(float rayon);

#endif
