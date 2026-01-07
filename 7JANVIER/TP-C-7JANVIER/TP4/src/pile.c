#include "pile.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 256

typedef struct {
  char data[MAX_SIZE];
  int top;
} CharStack;

typedef struct {
  int data[MAX_SIZE];
  int top;
} IntStack;

void init_char(CharStack *s) { s->top = -1; }
void push_char(CharStack *s, char c) {
  if (s->top < MAX_SIZE - 1) {
    s->data[++(s->top)] = c;
  } else {
    fprintf(stderr, "Erreur: Débordement de pile (CharStack overflow)\n");
  }
}
char pop_char(CharStack *s) {
  if (s->top >= 0) {
    return s->data[(s->top)--];
  }
  fprintf(stderr, "Erreur: Pile vide (CharStack underflow)\n");
  return '\0';
}
char peek_char(CharStack *s) {
  if (s->top >= 0) {
    return s->data[s->top];
  }
  return '\0';
}
int is_empty_char(CharStack *s) { return s->top == -1; }

void init_int(IntStack *s) { s->top = -1; }
void push_int(IntStack *s, int v) {
  if (s->top < MAX_SIZE - 1) {
    s->data[++(s->top)] = v;
  } else {
    fprintf(stderr, "Erreur: Débordement de pile (IntStack overflow)\n");
  }
}
int pop_int(IntStack *s) {
  if (s->top >= 0) {
    return s->data[(s->top)--];
  }
  fprintf(stderr, "Erreur: Pile vide (IntStack underflow)\n");
  return 0;
}

int precedence(char op) {
  if (op == '+' || op == '-')
    return 1;
  if (op == '*' || op == '/' || op == '%')
    return 2;
  return 0;
}

int is_operator(char c) { return strchr("+-*/%", c) != NULL; }

void normalize(const char *in, char *out) {
  int j = 0;
  for (int i = 0; in[i]; i++) {
    if (strchr("+-*/%()", in[i])) {
      out[j++] = ' ';
      out[j++] = in[i];
      out[j++] = ' ';
    } else {
      out[j++] = in[i];
    }
  }
  out[j] = '\0';
}

int evaluer(char *postfix) {
  IntStack pile;
  init_int(&pile);

  char temp[4096];
  strcpy(temp, postfix);
  char *token = strtok(temp, " ");

  while (token) {
    if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
      push_int(&pile, atoi(token));
    } else if (is_operator(token[0])) {
      int b = pop_int(&pile);
      int a = pop_int(&pile);
      switch (token[0]) {
      case '+':
        push_int(&pile, a + b);
        break;
      case '-':
        push_int(&pile, a - b);
        break;
      case '*':
        push_int(&pile, a * b);
        break;
      case '/':
        push_int(&pile, a / b);
        break;
      case '%':
        push_int(&pile, a % b);
        break;
      }
    }
    token = strtok(NULL, " ");
  }
  return pop_int(&pile);
}

void traiter(char *input) {
  char normalized[8192];
  normalize(input, normalized);

  CharStack pile;
  init_char(&pile);

  char output[4096] = "";
  char *token = strtok(normalized, " ");

  while (token) {
    if (isdigit(token[0])) {
      strcat(output, token);
      strcat(output, " ");
    } else if (token[0] == '(') {
      push_char(&pile, '(');
    } else if (token[0] == ')') {
      while (!is_empty_char(&pile) && peek_char(&pile) != '(') {
        int len = strlen(output);
        output[len] = pop_char(&pile);
        output[len + 1] = ' ';
        output[len + 2] = '\0';
      }
      pop_char(&pile); // Enlever '('
    } else if (is_operator(token[0])) {
      while (!is_empty_char(&pile) && peek_char(&pile) != '(' &&
             precedence(peek_char(&pile)) >= precedence(token[0])) {
        int len = strlen(output);
        output[len] = pop_char(&pile);
        output[len + 1] = ' ';
        output[len + 2] = '\0';
      }
      push_char(&pile, token[0]);
    }
    token = strtok(NULL, " ");
  }

  while (!is_empty_char(&pile)) {
    int len = strlen(output);
    output[len] = pop_char(&pile);
    output[len + 1] = ' ';
    output[len + 2] = '\0';
  }

  printf("Postfixe: %s\n", output);
  printf("Résultat: %d\n", evaluer(output));
}

/*
int main(void) {
  char input[4096];
  printf("Entrez une expression infixe : ");
  if (fgets(input, sizeof(input), stdin)) {
    input[strcspn(input, "\n")] = 0;
    traiter(input);
  }
  return 0;
}
*/
