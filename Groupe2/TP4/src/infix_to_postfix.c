#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK 100
#define MAX_OUTPUT 256

// Structure pour la pile d'opérateurs
typedef struct {
    char data[MAX_STACK];
    int top;
} Stack;

// Initialiser la pile
void init_stack(Stack *s) {
    s->top = -1;
}

// Vérifier si la pile est vide
int is_empty(Stack *s) {
    return s->top == -1;
}

// Vérifier si la pile est pleine
int is_full(Stack *s) {
    return s->top == MAX_STACK - 1;
}

// Empiler un élément
void push(Stack *s, char c) {
    if (!is_full(s)) {
        s->data[++(s->top)] = c;
    }
}

// Dépiler un élément
char pop(Stack *s) {
    if (!is_empty(s)) {
        return s->data[(s->top)--];
    }
    return '\0';
}

// Consulter le sommet de la pile sans dépiler
char peek(Stack *s) {
    if (!is_empty(s)) {
        return s->data[s->top];
    }
    return '\0';
}

// Déterminer la priorité d'un opérateur
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

// Vérifier si le caractère est un opérateur
int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Convertir une expression infixée en postfixée
char* infix_to_postfix(const char *infix) {
    Stack stack;
    init_stack(&stack);
    
    char *postfix = (char *)malloc(MAX_OUTPUT * sizeof(char));
    if (postfix == NULL) {
        return NULL;
    }
    
    int j = 0; // Index pour la chaîne de sortie
    int i = 0;
    
    while (infix[i] != '\0') {
        // Ignorer les espaces
        if (isspace(infix[i])) {
            i++;
            continue;
        }
        
        // Si c'est un chiffre (opérande)
        if (isdigit(infix[i])) {
            // Ajouter le nombre complet à la sortie
            while (isdigit(infix[i])) {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' '; // Ajouter un espace après le nombre
        }
        // Si c'est un opérateur
        else if (is_operator(infix[i])) {
            // Dépiler les opérateurs de priorité supérieure ou égale
            while (!is_empty(&stack) && 
                   precedence(peek(&stack)) >= precedence(infix[i])) {
                postfix[j++] = pop(&stack);
                postfix[j++] = ' ';
            }
            // Empiler l'opérateur courant
            push(&stack, infix[i]);
            i++;
        }
        else {
            // Caractère non reconnu
            i++;
        }
    }
    
    // Vider la pile dans la sortie
    while (!is_empty(&stack)) {
        postfix[j++] = pop(&stack);
        postfix[j++] = ' ';
    }
    
    // Supprimer l'espace final si présent
    if (j > 0 && postfix[j-1] == ' ') {
        j--;
    }
    
    postfix[j] = '\0'; // Terminer la chaîne
    
    return postfix;
}

int main() {
    const char *expression = "3 + 4 * 5";
    
    printf("Expression infixée : %s\n", expression);
    
    char *result = infix_to_postfix(expression);
    
    if (result != NULL) {
        printf("Expression postfixée : %s\n", result);
        free(result);
    } else {
        printf("Erreur lors de la conversion\n");
    }
    
    return 0;
}
