#include <stdio.h>
#include <stdbool.h>

#define MAX_COLORS 100

// Définition de la structure Color (typedef pour éviter de répéter `struct` à chaque fois)
typedef struct {
    unsigned char r, g, b, a;
} Color;

// Structure pour stocker les couleurs distinctes et leur nombre d'occurrences
typedef struct {
    Color color;
    int count;
} ColorCount;

// Fonction pour comparer deux couleurs (ici j'utilise bool de stdbool.h pour retourner vrai/faux, on pourrait aussi utiliser int pour retourner 1/0)
bool compare_colors(Color const c1, Color const c2) {
    return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a;
}

// Fonction pour afficher une couleur
void print_color(Color const color) {
    printf("R: %d, G: %d, B: %d, A: %d : \033[48;2;%d;%d;%dm  \033[0m ", color.r, color.g, color.b, color.a, color.r, color.g, color.b);
}

int main() {
    // Tableau de couleurs (100 couleurs max)
    Color colors[MAX_COLORS] = {
        {255, 0, 0, 255}, {0, 255, 0, 255}, {0, 0, 255, 255},
        {255, 0, 0, 255}, {255, 0, 0, 255}, {0, 255, 0, 255},
        {238, 123, 241, 255}, {238, 123, 241, 255}, {238, 123, 241, 255}
    };

    // Tableau pour stocker les couleurs distinctes et leurs occurrences
    ColorCount distinct_colors[MAX_COLORS];
    int distinct_count = 0;

    // Parcourir toutes les couleurs
    for (int i = 0; i < MAX_COLORS; i++) {
        bool found = false;

        // Vérifier si la couleur est déjà dans distinct_colors
        for (int j = 0; j < distinct_count; j++) {
            if (compare_colors(colors[i], distinct_colors[j].color)) {
                distinct_colors[j].count++;
                found = true;
                break;
            }
        }

        // Si la couleur est nouvelle, l'ajouter au tableau distinct_colors
        if (!found) {
            distinct_colors[distinct_count].color = colors[i];
            distinct_colors[distinct_count].count = 1;
            distinct_count++;
        }
    }

    // Afficher les résultats
    printf("Couleurs distinctes et occurrences :\n");
    for (int i = 0; i < distinct_count; i++) {
        print_color(distinct_colors[i].color);
        printf(" => Occurrences: %d\n", distinct_colors[i].count);
    }

    return 0;
}
