# Bibliothèques

* `string.h` : Bibliothèque standard pour les opérations sur les chaînes de caractères en C.
* `stdio.h` : Bibliothèque standard pour les entrées/sorties en C.
* `stdlib.h` : Bibliothèque standard pour les fonctions utilitaires en C.
* `stdbool.h` : Bibliothèque standard pour les types booléens en C.
* `dis` : Module Python pour l'analyse du bytecode.
* `math` : Module Python pour les fonctions mathématiques.

# Références

* [Documentation Python : Module `dis`](https://docs.python.org/3/library/dis.html)
* [Documentation Python : Module `math`](https://docs.python.org/3/library/math.html)
* [Documentation Python : Chaînes de caractères](https://docs.python.org/3/library/stdtypes.html#text-sequence-type-str)
* [Documentation Python : Classes](https://docs.python.org/3/tutorial/classes.html)
* [Documentation Python : F-strings](https://docs.python.org/3/tutorial/inputoutput.html)
* [Documentation C : Structures](https://openclassrooms.com/fr/courses/19980-apprenez-a-programmer-en-c/16119-creez-vos-propres-types-de-variables)
* [Documentation C : Les pointeurs](https://zestedesavoir.com/tutoriels/755/le-langage-c-1/1043_aggregats-memoire-et-fichiers/4277_les-pointeurs/)
* [W3Schools : C Strings](https://www.w3schools.in/c-tutorial/strings/)
* [W3Schools : Python Strings](https://www.w3schools.com/python/python_strings.asp)
* [Stack Overflow (Pour les bugs)](https://stackoverflow.com/)
* [ChatGPT (pour les bugs si réponse non trouvée sur StackOverflow)](https://chatgpt.com/)

# Difficulté

* 2/10 - Assez Facile

# Commentaires

## Questions

### 2.1

Vu en Cours avec Mr John SAMUEL

### 2.2

Toutes les commandes ont été exécutées avec succès.

### 2.3

#### Exemple 1

1. Exécuter et observer le bytecode :
    * La sortie du module 'dis' affiche le bytecode de la fonction 'calculer_aire' en Python.
    * Fait
2. Explication des instructions :
    * Fait
3. Expérimentation :
    * En remplacant le calcul d'air (math.pi * rayon * rayon) par une constant (e.g. 42),
      la sortie du bytecode change et on retrouve qu'une seule instruction qui est de retourner la valeur 42 (
      RETURN_CONST).
4. Réflexion sur l'optimisation :
    * Lorsqu'on remplace l'opération par une constante, le bytecode passe de :
    ```txt
    5             0 RESUME                   0
    6             2 LOAD_GLOBAL              0 (math)
                 12 LOAD_ATTR                2 (pi)
                 32 LOAD_FAST                0 (rayon)
                 34 BINARY_OP                5 (*)
                 38 LOAD_FAST                0 (rayon)
                 40 BINARY_OP                5 (*)
                 44 RETURN_VALUE
    ```
   à :
    ```txt
    5             0 LOAD_CONST               0 
    6             2 RETURN_VALUE             1 (42)
    ```
   On peut donc dire que le bytecode est optimisé en remplaçant l'opération par une constante.

----------------------------------------------------------------------------------------------------------------------------

1. Que fait chaque instruction du bytecode ?
    * `LOAD_GLOBAL` : Charge une variable globale.
    * `LOAD_FAST` : Charge une variable locale.
    * `BINARY_MULTIPLY` : Multiplie les deux valeurs au sommet de la pile.
2. Modification de l’expression :
    * Fait
3. Comment fonctionne la pile d’exécution ?
    * La pile d'exécution est une structure de données qui stocke les valeurs intermédiaires des opérations effectuées.
    * Lorsqu'une opération est effectuée, les valeurs sont placées sur la pile et le résultat est stocké à la place des
      valeurs.
    * Les opérations suivantes utilisent les valeurs stockées sur la pile.

----------------------------------------------------------------------------------------------------------------------------

#### Exemple 2

1. Analyser le bytecode d'une boucle `for` :
    * Le bytecode de la boucle `for` affiche les instructions pour charger la variable `i`, vérifier la condition de la
      boucle, exécuter le bloc de code de la boucle, et incrémenter la variable `i`.
   ```
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
   ```
   
2. Explication des instructions :
    * `LOAD_GLOBAL` : Charge une variable globale.
    * `LOAD_FAST` : Charge une variable locale.
    * `CALL` : Appelle une fonction.
    * `GET_ITER` : Récupère un itérateur.
    * `FOR_ITER` : Itère sur un itérateur.
    * `STORE_FAST` : Stocke une variable locale.
    * `BINARY_OP` : Effectue une opération binaire.
    * `JUMP_BACKWARD` : Saute en arrière dans le code.
    * `END_FOR` : Fin de la boucle `for`.

3. Expérimentation :
   * Avec une boucle `while`:
   ```
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
   ```

4. Différences entre le bytecode de la boucle `for` et celui de la boucle `while` :
    * La boucle `for` utilise une instruction `FOR_ITER` pour itérer sur un itérateur, tandis que la boucle `while` utilise
      des instructions de comparaison et de saut conditionnel pour contrôler l'itération.
    * La boucle `for` est généralement plus compacte et plus lisible, tandis que la boucle `while` offre plus de
      flexibilité pour des conditions d'arrêt complexes.

----------------------------------------------------------------------------------------------------------------------------

### 2.4

1. `chaine.py` -> Code rédigé et testé.
2. `chaine.c` -> Code rédigé et testé.

----------------------------------------------------------------------------------------------------------------------------

### 2.5

1. `bd_école.py` -> Code rédigé et testé.
2. `bd_école.c` -> Code rédigé et testé.

----------------------------------------------------------------------------------------------------------------------------

### 2.6

1. `phrases.py` -> Code rédigé et testé.
2. `phrases.c` -> Code rédigé et testé.

----------------------------------------------------------------------------------------------------------------------------

### 2.7

1. `couleurs.py` -> Code rédigé et testé.
2. `couleurs.c` -> Code rédigé et testé.

----------------------------------------------------------------------------------------------------------------------------


