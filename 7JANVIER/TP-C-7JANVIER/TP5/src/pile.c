#include "pile.h"
#include "symbols.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 256

typedef struct {
  char data[MAX_SIZE];
  int top;
} CharStack;

typedef struct {
  double data[MAX_SIZE];
  int top;
} DoubleStack;

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

void init_double(DoubleStack *s) { s->top = -1; }
void push_double(DoubleStack *s, double v) {
  if (s->top < MAX_SIZE - 1) {
    s->data[++(s->top)] = v;
  } else {
    fprintf(stderr, "Erreur: Débordement de pile (DoubleStack overflow)\n");
  }
}
double pop_double(DoubleStack *s) {
  if (s->top >= 0) {
    return s->data[(s->top)--];
  }
  fprintf(stderr, "Erreur: Pile vide (DoubleStack underflow)\n");
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

static int eval_error = 0;

double evaluer(char *postfix) {
  eval_error = 0;
  DoubleStack pile;
  init_double(&pile);

  char temp[4096];
  strcpy(temp, postfix);
  char *token = strtok(temp, " ");

  while (token) {
    if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
      push_double(&pile, atof(token));
    } else if (is_operator(token[0]) && strlen(token) == 1) {
      if (pile.top < 1) {
        fprintf(stderr, "Erreur : Expression mal formée\n");
        eval_error = 1;
        return 0;
      }
      double b = pop_double(&pile);
      double a = pop_double(&pile);
      switch (token[0]) {
      case '+':
        push_double(&pile, a + b);
        break;
      case '-':
        push_double(&pile, a - b);
        break;
      case '*':
        push_double(&pile, a * b);
        break;
      case '/':
        if (b == 0) {
          fprintf(stderr, "Erreur : division par zéro\n");
          eval_error = 1;
          push_double(&pile, 0);
        } else
          push_double(&pile, a / b);
        break;
      case '%':
        push_double(&pile, fmod(a, b));
        break;
      }
    } else {
      VarValue v;
      if (get_variable(token, &v) == 0) {
        if (v.type == TYPE_INT)
          push_double(&pile, (double)v.value.i_val);
        else if (v.type == TYPE_REAL)
          push_double(&pile, v.value.r_val);
      } else {
        fprintf(stderr, "Erreur : variable non définie %s\n", token);
        eval_error = 1;
        push_double(&pile, 0);
      }
    }
    token = strtok(NULL, " ");
  }
  if (pile.top != 0) {
    eval_error = 1;
  }
  return (pile.top == 0) ? pop_double(&pile) : 0;
}

void infix_to_postfix(const char *input, char *output) {
  char normalized[8192];
  normalize(input, normalized);

  CharStack pile;
  init_char(&pile);

  output[0] = '\0';
  char *temp_norm = strdup(normalized);
  if (temp_norm == NULL) {
    fprintf(stderr, "Memory allocation failed in infix_to_postfix\n");
    return;
  }
  char *token = strtok(temp_norm, " ");

  while (token) {
    if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
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
    } else if (token[0] != '(' && token[0] != ')') {
      // Variable (supports UTF-8 as it's not a digit/op/paren)
      strcat(output, token);
      strcat(output, " ");
    }
    token = strtok(NULL, " ");
  }

  while (!is_empty_char(&pile)) {
    int len = strlen(output);
    output[len] = pop_char(&pile);
    output[len + 1] = ' ';
    output[len + 2] = '\0';
  }
  free(temp_norm);
}

void traiter(char *input) {
  char output[4096];
  infix_to_postfix(input, output);
  if (strlen(output) > 0) {
    double res = evaluer(output);
    if (!eval_error) {
      printf("%g\n", res);
    }
  }
}
