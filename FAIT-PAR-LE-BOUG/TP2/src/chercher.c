/*
 * Nom du fichier : chercher.c
 * Objectif : Rechercher une phrase dans un tableau de phrases sans utiliser de fonctions de bibliothèque standard pour la recherche.
 * Auteurs : Adrian RABIAN, Quentin BASTOS
 * Commande pour exécuter le fichier : gcc chercher.c -o chercher && ./chercher
 */
#include <stdio.h>

// Fonction pour calculer la longueur d'une chaîne (pour éviter strlen)
int ma_strlen(const char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// Fonction pour comparer deux chaînes (pour éviter strcmp)
int ma_strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

int main() {
    // Tableau de 10 phrases
    const char *phrases[10] = {
        "Bonjour, comment ça va ?",
        "Le temps est magnifique aujourd'hui.",
        "C'est une belle journée.",
        "La programmation en C est amusante.",
        "Les tableaux en C sont puissants.",
        "Les pointeurs en C peuvent être déroutants.",
        "Il fait beau dehors.",
        "La recherche dans un tableau est intéressante.",
        "Les structures de données sont importantes.",
        "Programmer en C, c'est génial."
    };

    char recherche[100] = "La programmation en C est amusante.";
    // Pour tester une phrase non trouvée, décommentez la ligne suivante :
    // char recherche[100] = "Je préfère le Python.";

    int trouve = 0;

    // Recherche de la phrase dans le tableau
    for (int i = 0; i < 10; i++) {
        if (ma_strcmp(phrases[i], recherche) == 0) {
            trouve = 1;
            break;
        }
    }

    if (trouve) {
        printf("Phrase trouvée\n");
    } else {
        printf("Phrase non trouvée\n");
    }

    return 0;
}
