#include <stdio.h>

int main()
{
    int taille;

    // Demander la taille du triangle
    printf("Entrez la taille du triangle (strictement inférieure à 10) : ");
    scanf("%d", &taille);

    // Vérifier que la taille est bien inférieure à 10
    if (taille >= 10)
    {
        printf("La taille doit être strictement inférieure à 10.\n");
        return 1;
    }


    // Boucle For
    for (int i = 1; i <= taille; i++)
    {
        // Pour chaque ligne, on affiche i étoiles
        for (int j = 1; j <= i; j++)
        {
            // Si on est sur la première colonne, la dernière colonne ou la dernière ligne, on affiche une étoile
            if (j == 1 || j == i || i == taille)
            {
                printf("* ");
            }
            else
            {
                printf("# ");
            }
        }
        printf("\n");
    }

    // Boucle While
    int i = 1;
    while (i <= taille)
    {
        int j = 1;
        // Pour chaque ligne, on affiche i étoiles
        while (j <= i)
        {
            // Si on est sur la première colonne, la dernière colonne ou la dernière ligne, on affiche une étoile
            if (j == 1 || j == i || i == taille)
            {
                printf("* ");
            }
            else
            {
                printf("# ");
            }
            j++;
        }
        printf("\n");
        i++;
    }

    // Avec do...while
    int i_2 = 1;
    do {
        int j = 1;
        do {
            if (j == 1 || j == i_2 || i_2 == taille) {
                printf("* ");
            } else {
                printf("# ");
            }
            j++;
        } while (j <= i_2);
        printf("\n");
        i_2++;
    } while (i_2 <= taille);

    return 0;
}
