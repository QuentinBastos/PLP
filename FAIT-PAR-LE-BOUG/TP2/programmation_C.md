# Rapport de Synthèse : Programmation en C

## 1. Débogage avec GDB
GDB (GNU Debugger) est un outil puissant pour analyser l'exécution d'un programme, comprendre les erreurs (comme les erreurs de segmentation) et inspecter l'état de la mémoire.
Commandes principales :
- `gcc -ggdb3 fichier.c -o fichier` : Compiler avec les symboles de débogage.
- `gdb ./fichier` : Lancer GDB.
- `run` (ou `r`) : Exécuter le programme.
- `break` (ou `b`) : Poser un point d'arrêt.
- `next` (ou `n`) : Exécuter la ligne suivante.
- `print` (ou `p`) : Afficher la valeur d'une variable.
- `bt` (backtrace) : Afficher la pile d'appels.

## 2. Chaîne de compilation avec GCC
La compilation en C se fait en plusieurs étapes :
1. **Préprocesseur** (`gcc -E`) : Traitement des directives `#include`, `#define`.
2. **Compilation** (`gcc -S`) : Traduction en assembleur.
3. **Assemblage** (`gcc -c`) : Création des fichiers objets (`.o`).
4. **Édition de liens** : Création de l'exécutable final en liant les objets et les bibliothèques.

## 3. Manipulation de chaînes de caractères
Les chaînes en C sont des tableaux de caractères terminés par `\0`.
- **Longueur** : On parcourt jusqu'au `\0`.
- **Copie** : On copie caractère par caractère.
- **Concaténation** : On ajoute les caractères de la source à la fin de la destination (en écrasant le `\0` initial).

## 4. Gestion des structures et recherche
- **Structures** : Permettent de regrouper des données hétérogènes (ex: `struct Etudiant`).
- **Recherche** : On peut lire un fichier ligne par ligne avec `fgets` et rechercher des sous-chaînes avec `strstr` ou des algorithmes manuels.
