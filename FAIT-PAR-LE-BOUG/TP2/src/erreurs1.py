from typing import List
import pdb


def double_values(tableau: List[int]) -> None:  # ERREUR 1: Le type de retour est incorrect il devrait être List[int]
    for compteur in range(len(tableau)):
        # Introduire une erreur : parfois multiplier par 3 au lieu de 2
        if compteur % 2 == 0:  # ERREUR 2: La condition est incorrecte, il ne devrait pas y avoir de vérification de parité on devrait multiplier par 2 directement
            tableau[compteur] *= 2
        else:
            tableau[compteur] *= 3  # ERREUR 3: Ligne inutile
        # Insérer un point d'arrêt pour observer la valeur de 'tableau' à chaque étape
        pdb.set_trace()

    return tableau


# Créer un tableau d'exemple
tableau: List[int] = [1, 2, 3, 4, 5]

# Appeler la fonction et stocker le résultat
resultat = double_values(tableau)

# Afficher le résultat final
print(resultat)
