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

