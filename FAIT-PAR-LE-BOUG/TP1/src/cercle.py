import math

if __name__ == "__main__":
    # Calcul de l'aire et du périmètre d'un cercle
    rayon: float = int(input("Rayon du cercle (cm) : "))
    aire: float = math.pi * rayon * rayon
    perimeter: float = 2 * math.pi * rayon

    # Affichage des résultats
    print(f"L'aire du cercle : {aire} cm2 \nLe périmètre du cercle : {perimeter} cm")
