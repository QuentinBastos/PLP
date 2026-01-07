#include "pile.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SZ 256

typedef struct {
  char items[SZ];
  int idx;
} StackChar;

typedef struct {
  int items[SZ];
  int idx;
} StackInt;

// --- Char Stack ---
void s_char_init(StackChar *s) { s->idx = -1; }
void s_char_add(StackChar *s, char c) {
  if (s->idx < SZ - 1) s->items[++s->idx] = c;
}
char s_char_pop(StackChar *s) {
  return (s->idx >= 0) ? s->items[s->idx--] : 0;
}
char s_char_peek(StackChar *s) {
  return (s->idx >= 0) ? s->items[s->idx] : 0;
}
int s_char_empty(StackChar *s) { return s->idx == -1; }

// --- Int Stack ---
void s_int_init(StackInt *s) { s->idx = -1; }
void s_int_add(StackInt *s, int v) {
  if (s->idx < SZ - 1) s->items[++s->idx] = v;
}
int s_int_pop(StackInt *s) {
  return (s->idx >= 0) ? s->items[s->idx--] : 0;
}

// --- Utils ---
int get_prec(char c) {
  if (c == '*' || c == '/' || c == '%') return 2;
  if (c == '+' || c == '-') return 1;
  return 0;
}

int is_op(char c) {
  return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}

void clean_str(const char *src, char *dst) {
  int j = 0;
  for (int i = 0; src[i]; i++) {
    char c = src[i];
    if (is_op(c) || c == '(' || c == ')') {
      dst[j++] = ' '; dst[j++] = c; dst[j++] = ' ';
    } else {
      dst[j++] = c;
    }
  }
  dst[j] = 0;
}

// --- Logic ---
int compute_postfix(char *expr) {
  StackInt s;
  s_int_init(&s);
  char buf[4096];
  strcpy(buf, expr);
  char *tok = strtok(buf, " ");

  while (tok) {
    if (isdigit(tok[0]) || (tok[0] == '-' && isdigit(tok[1]))) {
      s_int_add(&s, atoi(tok));
    } else if (is_op(tok[0])) {
      int v2 = s_int_pop(&s);
      int v1 = s_int_pop(&s);
      switch(tok[0]) {
        case '+': s_int_add(&s, v1 + v2); break;
        case '-': s_int_add(&s, v1 - v2); break;
        case '*': s_int_add(&s, v1 * v2); break;
        case '/': if(v2) s_int_add(&s, v1 / v2); break;
        case '%': if(v2) s_int_add(&s, v1 % v2); break;
      }
    }
    tok = strtok(NULL, " ");
  }
  return s_int_pop(&s);
}

void handle_infix_expr(char *raw) {
  char clean[8192];
  clean_str(raw, clean);

  StackChar s;
  s_char_init(&s);
  
  char post[4096] = "";
  char *tok = strtok(clean, " ");

  while (tok) {
    if (isdigit(tok[0])) {
      strcat(post, tok); strcat(post, " ");
    } else if (tok[0] == '(') {
      s_char_add(&s, '(');
    } else if (tok[0] == ')') {
      while (!s_char_empty(&s) && s_char_peek(&s) != '(') {
        int l = strlen(post);
        post[l] = s_char_pop(&s); post[l+1] = ' '; post[l+2] = 0;
      }
      s_char_pop(&s); // Remove (
    } else if (is_op(tok[0])) {
      while (!s_char_empty(&s) && s_char_peek(&s) != '(' &&
             get_prec(s_char_peek(&s)) >= get_prec(tok[0])) {
        int l = strlen(post);
        post[l] = s_char_pop(&s); post[l+1] = ' '; post[l+2] = 0;
      }
      s_char_add(&s, tok[0]);
    }
    tok = strtok(NULL, " ");
  }

  while (!s_char_empty(&s)) {
    int l = strlen(post);
    post[l] = s_char_pop(&s); post[l+1] = ' '; post[l+2] = 0;
  }

  printf("Postfixe: %s\n", post);
  printf("Résultat: %d\n", compute_postfix(post));
}
