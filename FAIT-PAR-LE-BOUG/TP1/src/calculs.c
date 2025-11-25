#include <stdio.h>

int main()
{
    int num1;
    int num2;
    char op;

    // Demander les valeurs et l'opérateur
    printf("Valeur 1 : \n");
    scanf("%d", &num1);
    printf("Entrez un opérateur : ");
    scanf(" %c", &op); // Note the space before %c to ignore whitespace

    // Si l'opérateur est un opérateur `unaire`, on ne demande pas la deuxième valeur
    if (op != '~')
    {
        printf("Valeur 2 : \n");
        scanf("%d", &num2);
    }

    // Calculer et afficher le résultat
    switch (op)
    {
    case '+':
        printf("%d %c %d = %d\n", num1, op, num2, num1 + num2);
        break;
    case '-':
        printf("%d %c %d = %d\n", num1, op, num2, num1 - num2);
        break;
    case '*':
        printf("%d %c %d = %d\n", num1, op, num2, num1 * num2);
        break;
    case '/':
        if (num2 != 0)
            printf("%d %c %d = %d\n", num1, op, num2, num1 / num2);
        else
            printf("Erreur : division par zéro\n");
        break;
    case '%':
        if (num2 != 0)
            printf("%d %c %d = %d\n", num1, op, num2, num1 % num2);
        else
            printf("Erreur : division par zéro\n");
        break;
    case '&':
        printf("%d %c %d = %d\n", num1, op, num2, num1 & num2);
        break;
    case '|':
        printf("%d %c %d = %d\n", num1, op, num2, num1 | num2);
        break;
    case '~':
        printf("%c%d = %d\n", op, num1, ~num1);
        break;
    default:
        printf("Opérateur invalide\n");
        break;
    }

    return 0;
}
