class Color:
    def __init__(self, r, g, b, a):
        self.r = r
        self.g = g
        self.b = b
        self.a = a

    # __eq__ est une fonction par défaut dans une classe python qui permet de comparer deux objets
    def __eq__(self, other):
        return (self.r == other.r and
                self.g == other.g and
                self.b == other.b and
                self.a == other.a)

    # Méthode pour afficher une couleur
    def __str__(self):
        return f"R: {self.r}, G: {self.g}, B: {self.b}, A: {self.a}"


class ColorCount:
    def __init__(self, color):
        self.color = color
        self.count = 1


def print_color(color):
    # Fonction pour afficher une couleur et simuler une couleur de fond dans le terminal
    print(f"R: {color.r}, G: {color.g}, B: {color.b}, A: {color.a} ", end="")
    print(f"\033[48;2;{color.r};{color.g};{color.b}m  \033[0m", end="")


if __name__ == "__main__":
    # Tableau de couleurs prédéfinies (en python, il n'y a pas vraiment de limite contrairement en C)
    colors = [
        Color(255, 0, 0, 255), Color(0, 255, 0, 255), Color(0, 0, 255, 255),
        Color(255, 0, 0, 255), Color(255, 0, 0, 255), Color(0, 255, 0, 255),
        Color(238, 123, 241, 255), Color(238, 123, 241, 255), Color(238, 123, 241, 255)
    ]

    # Liste pour stocker les couleurs distinctes et leurs occurrences
    distinct_colors = []

    # Parcourir toutes les couleurs
    for color in colors:
        found = False  # bool est déjà un type primitif en python contrairement à C ou j'ai dû importer stdbool.h

        # Vérifier si la couleur est déjà dans distinct_colors
        for distinct_color in distinct_colors:
            if color == distinct_color.color:
                distinct_color.count += 1
                found = True
                break

        # Si la couleur est nouvelle, l'ajouter à la liste distinct_colors
        if not found:
            distinct_colors.append(ColorCount(color))

    # Afficher les résultats
    print("Couleurs distinctes et occurrences :")
    for distinct_color in distinct_colors:
        print_color(distinct_color.color)
        print(f" => Occurrences: {distinct_color.count}")
