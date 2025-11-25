#include <stdio.h>
#include <string.h>

int main() {
    char filename[100], phrase[100], line[256];
    FILE *file;
    int line_number = 0, found = 0;

    // Demander le nom du fichier et la phrase à rechercher
    printf("Entrez le nom du fichier : ");
    scanf("%s", filename);
    printf("Entrez la phrase que vous souhaitez rechercher : ");
    getchar();  // Pour consommer le '\n' après scanf
    fgets(phrase, sizeof(phrase), stdin);
    phrase[strcspn(phrase, "\n")] = '\0';  // Supprimer le retour à la ligne

    // Ouvrir le fichier
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    printf("\nRésultats de la recherche :\n");

    // Lire le fichier ligne par ligne et rechercher la phrase
    while (fgets(line, sizeof(line), file)) {
        line_number++;  // incrémenter le numéro de ligne
        int count = 0;
        char *pos = line;

        // Compter le nombre d'occurrences de la phrase dans la ligne
        while ((pos = strstr(pos, phrase)) != NULL) {
            count++;
            pos += strlen(phrase);  // Avancer après la phrase trouvée
        }

        if (count > 0) {
            printf("Ligne %d => %d occurrence(s)\n", line_number, count);
            found = 1;
        }
    }

    // Si aucune occurrence n'a été trouvée
    if (!found) {
        printf("Aucune occurrence trouvée.\n");
    }

    // Fermer le fichier
    fclose(file);
    return 0;
}
