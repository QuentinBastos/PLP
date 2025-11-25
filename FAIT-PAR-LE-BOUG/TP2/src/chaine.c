#include <stdio.h>

int longueur(char *chaine) {
    int i = 0;
    // tant qu'on arrive pas au caractère de fin de chaine
    // on incrémente i
    while (chaine[i] != '\0') {
        i++;
    }
    return i;
}

void copie(char *dest, char *src) {
    int i = 0;  // indice de parcours de la chaine

    // tant qu'on arrive pas au caractère de fin de chaine
    while (src[i] != '\0') {
        dest[i] = src[i]; // copie du caractère src[i] dans dest[i]
        i++;  // on passe au caractère suivant
    }
    dest[i] = '\0';  // on ajoute le caractère de fin de chaine à la fin de dest
}

void concatene(char *dest, char *src) {
    int i = longueur(dest);  // on récupère la longueur de dest
    int j = 0; // indice de parcours de la chaine src

    // on copie les caractères de src à la suite de ceux de dest
    while (src[j] != '\0') {
        dest[i] = src[j]; // copie du caractère src[j] dans dest[i]
        i++; // on passe au caractère suivant
        j++; // on passe au caractère suivant
    }
    dest[i] = '\0';  // on ajoute le caractère de fin de chaine à la fin de dest
}


int main() {
    // déclaration des variables
    char chaine1[100];
    char chaine2[100];
    char chaine3[100]; // chaine pour stocker le résultat des opérations

    printf("Saisir une chaine de caractere : ");
    scanf("%s", chaine1);  // ajouter l'entrée dans chaine 1

    printf("Saisir une autre chaine de caractere : ");
    scanf("%s", chaine2);  // ajouter l'entrée dans chaine 2

    printf("Longueur de chaine1 : %d\n", longueur(chaine1));
    printf("Longueur de chaine2 : %d\n", longueur(chaine2));

    copie(chaine3, chaine1);  // copie de chaine1 dans chaine3
    printf("Copie de chaine1 dans chaine3 : %s\n", chaine3);

    concatene(chaine3, chaine2); // concaténation de chaine1 et chaine2 dans chaine3
    printf("Concatenation de chaine1 et chaine2 dans chaine3 : %s\n", chaine3);

    return 0;
}

