/*
 * Nom du fichier : erreurs.c
 * Objectif : Identifier et corriger des erreurs dans un programme C.
 * Auteurs : Adrian RABIAN, Quentin BASTOS
 * Lignes importantes : 5, 8, 9
 * Commande pour exécuter le fichier : gcc erreurs.c -o erreurs && ./erreurs
 */
#include <stdio.h>

int main() {

   int tableau[100];

   printf("Tableau : ");
   for (int compteur = 0; compteur < (sizeof(tableau)/sizeof(int)); compteur++) {
       tableau[compteur] = tableau[compteur] * 2;
       printf("%d ", tableau[compteur]);
   }

   printf("\n");

   return (0);

}

