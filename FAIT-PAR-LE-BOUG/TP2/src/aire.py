import math


# Fonction pour calculer l'aire : pi * R * R
def calculer_aire(rayon: float) -> float:
    # LOAD_GLOBAL (math) and LOAD_ATTR (pi)
    return math.pi * rayon * rayon  # pi  *(BINARY_OP) LOAD_FAST(rayon) *(BINARY_OP) LOAD_FAST(rayon)
    # return 42  # LOAD_CONST and RETURN_VALUE
    # RETURN_VALUE


def main() -> None:
    rayon: float = 5.0  # LOAD_CONST and STORE_FAST
    aire: float = calculer_aire(rayon)  # LOAD_GLOBAL and LOAD_FAST then => CALL and STORE_FAST
    print(f"L'aire du cercle de rayon {rayon:.2f} est {aire:.2f}")


if __name__ == "__main__":
    main()

"""
Ex 1:

1. Exécuter et observer le bytecode :
   La sortie du module 'dis' affiche le bytecode de la fonction 'calculer_aire' en Python.


3. Expérimentation :
   En replaçant le calcul d'air (math.pi * rayon * rayon) par une constante (e.g. 42), 
   la sortie du bytecode change et on retrouve qu'une seule instruction qui est de retourner la valeur 42 (RETURN_CONST).

Que fait chaque instruction du bytecode ?
LOAD_GLOBAL : Charge une variable globale.
LOAD_FAST : Charge une variable locale.
BINARY_MULTIPLY : Multiplie les deux valeurs au sommet de la pile.

Comment fonctionne la pile d’exécution ?
- La pile d'exécution est une structure de données qui stocke les valeurs intermédiaires des opérations effectuées.
- Lorsqu'une opération est effectuée, les valeurs sont placées sur la pile et le résultat est stocké à la place des valeurs.
- Les opérations suivantes utilisent les valeurs stockées sur la pile.
"""