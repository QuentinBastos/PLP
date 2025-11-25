#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // Nécessaire pour utiliser strcpy()

struct Etudiant {
    char nom[100];
    char prenom[100];
    char adresse[100];
    int *notes;
    int nombre_notes;
};

void afficher_etudiant(struct Etudiant etudiant) {
    printf("Nom : %s\n", etudiant.nom);
    printf("Prenom : %s\n", etudiant.prenom);
    printf("Adresse : %s\n", etudiant.adresse);
    printf("Notes : ");
    for (int i = 0; i < etudiant.nombre_notes; i++) {
        printf("%d ", etudiant.notes[i]);
    }
    printf("\n");
}

int main() {
    struct Etudiant etudiants[5];  // Tableau de 5 étudiants

    for (int i = 0; i < 5; i++) {
        printf("Saisir les informations pour l'etudiant.e %d\n", i + 1);
        printf("=========================================\n");
        char buffer[100];  // Buffer temporaire pour stocker les entrées de l'utilisateur

        // Saisie des informations avec strcpy
        printf("Saisir le nom de l'etudiant.e : ");
        scanf("%s", buffer);
        strcpy(etudiants[i].nom, buffer);
        printf("Saisir le prenom de l'etudiant.e : ");
        scanf("%s", buffer);
        strcpy(etudiants[i].prenom, buffer);
        printf("Saisir l'adresse de l'etudiant.e : ");
        scanf("%s", buffer);
        strcpy(etudiants[i].adresse, buffer);

        // Saisie du nombre de notes pour allouer la mémoire dynamiquement
        printf("Combien de notes voulez-vous saisir ? ");
        scanf("%d", &etudiants[i].nombre_notes);

        // Vérification que le nombre de notes est valide
        if (etudiants[i].nombre_notes <= 0) {
            printf("Nombre de notes invalide.\n");
            return 1;
        }

        // Allocation dynamique de la mémoire pour les notes
        etudiants[i].notes = (int*)malloc(etudiants[i].nombre_notes * sizeof(int));
        if (etudiants[i].notes == NULL) {
            printf("Erreur d'allocation de mémoire\n");
            return 1;
        }

        // Saisie des notes de l'étudiant et stockage dans le tableau dynamique
        for (int j = 0; j < etudiants[i].nombre_notes; j++) {
            printf("Note %d: ", j + 1);
            scanf("%d", &etudiants[i].notes[j]);
        }
    }

    // Affichage des informations des étudiants avec la fonction afficher_etudiant
    for (int i = 0; i < (sizeof(etudiants) / sizeof(etudiants[0])); i++) {
        printf("Informations pour l'etudiant.e %d\n", i + 1);
        printf("=========================================\n");
        afficher_etudiant(etudiants[i]);

        free(etudiants[i].notes);  // Libérer la mémoire allouée dynamiquement pour les notes
        etudiants[i].notes = NULL;  // Bonne pratique : on annule le pointeur après libération
    }

    return 0;
}
