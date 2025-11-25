import dis  # IMPORT_NAME and STORE_NAME


# def calculer_somme(n: int) -> int:
#     somme = 0 # LOAD_CONST and STORE_FAST
#     for i in range(n): # LOAD_FAST(n) and GET_ITER and FOR_ITER
#         somme += i # LOAD_FAST(somme) and LOAD_FAST(i) and INPLACE_ADD
#     return somme # LOAD_FAST(somme) and RETURN_VALUE


def calculer_somme(n: int) -> int:
    somme = 0  # LOAD_CONST and STORE_FAST
    i = 0  # LOAD_CONST and STORE_FAST
    while i < n:  # LOAD_FAST(i) COMPARE_OP(<) LOAD_FAST(n) -> POP_JUMP_IF_FALSE -> JUMP_BACKWARD
        somme += i  # LOAD_FAST(somme)  BINARY_OP(+=) LOAD_FAST(i) STORE_FAST(somme)
        i += 1  # LOAD_FAST(i)  BINARY_OP(+=) LOAD_CONST(1) STORE_FAST(i)
    return somme  # LOAD_FAST(somme) RETURN_VALUE


def main() -> None:
    n = 10  # LOAD_CONST(10) STORE_FAST(n)
    result = calculer_somme(n)  # LOAD_GLOBAL(calculer_somme()) LOAD_FAST(n) CALL -> STORE_FAST(result)
    print(f"La somme des entiers de 0 à {n - 1} est {result}")


if __name__ == "__main__":
    # Utilisation de dis pour afficher le bytecode de la fonction
    dis.dis(calculer_somme)
    main()

"""
1. Analyser le bytecode d'une boucle for :
    Le bytecode de la boucle for affiche les instructions pour charger la variable i, 
    vérifier la condition de la boucle, exécuter le bloc de code de la boucle, et incrémenter la variable i.
      6           6 LOAD_GLOBAL              1 (NULL + range)
                 16 LOAD_FAST                0 (n)
                 18 CALL                     1
                 26 GET_ITER
            >>   28 FOR_ITER                 7 (to 46)
                 32 STORE_FAST               2 (i)
    
      7          34 LOAD_FAST                1 (somme)
                 36 LOAD_FAST                2 (i)
                 38 BINARY_OP               13 (+=)
                 42 STORE_FAST               1 (somme)
                 44 JUMP_BACKWARD            9 (to 28)
    
      6     >>   46 END_FOR
      
2. Explication des instructions :
    - LOAD_GLOBAL : Charge une variable globale.
    - LOAD_FAST : Charge une variable locale.
    - CALL : Appelle une fonction.
    - GET_ITER : Récupère un itérateur.
    - FOR_ITER : Itère sur un itérateur.
    - STORE_FAST : Stocke une variable locale.
    - BINARY_OP : Effectue une opération binaire.
    - JUMP_BACKWARD : Saute en arrière dans le code.
    - END_FOR : Fin de la boucle for.
    
3. Expérimentation :
    Avec une boucle while:
     15     >>   20 LOAD_FAST                1 (somme)
                 22 LOAD_FAST                2 (i)
                 24 BINARY_OP               13 (+=)
                 28 STORE_FAST               1 (somme)
    
     16          30 LOAD_FAST                2 (i)
                 32 LOAD_CONST               2 (1)
                 34 BINARY_OP               13 (+=)
                 38 STORE_FAST               2 (i)
    
     14          40 LOAD_FAST                2 (i)
                 42 LOAD_FAST                0 (n)
                 44 COMPARE_OP               2 (<)
                 48 POP_JUMP_IF_FALSE        1 (to 52)
                 50 JUMP_BACKWARD           16 (to 20)
    
     17     >>   52 LOAD_FAST                1 (somme)
                 54 RETURN_VALUE

4. Différences entre le bytecode de la boucle for et celui de la boucle while :
    - La boucle for utilise une instruction FOR_ITER pour itérer sur un itérateur, 
    tandis que la boucle while utilise des instructions de comparaison et de saut conditionnel pour contrôler l'itération.
    - La boucle for est généralement plus compacte et plus lisible, 
    tandis que la boucle while offre plus de flexibilité pour des conditions d'arrêt complexes.
"""
