#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void pass_spaces(const char **ptr) {
  if (!ptr || !*ptr) return;
  while (isspace((unsigned char)**ptr)) (*ptr)++;
}

Token extract_num(const char **ptr) {
  Token t;
  t.type = TOKEN_NUMBER;
  int i = 0;
  int dots = 0;

  if (!ptr || !*ptr) {
    t.type = TOKEN_UNKNOWN;
    t.value[0] = 0;
    return t;
  }

  for (; **ptr; (*ptr)++) {
    char c = **ptr;
    if (!isdigit((unsigned char)c) && c != '.') break;
    if (c == '.') {
      if (++dots > 1) break;
    }
    if (i < 63) t.value[i++] = c;
  }
  t.value[i] = 0;
  return t;
}

Token extract_op(const char **ptr) {
  Token t;
  t.type = TOKEN_OPERATOR;
  t.value[0] = 0;
  if (!ptr || !*ptr || !**ptr) {
    t.type = TOKEN_UNKNOWN;
    return t;
  }
  t.value[0] = **ptr;
  t.value[1] = 0;
  (*ptr)++;
  return t;
}

int tokenize(const char *in, Token *out) {
  const char *cur = in;
  int n = 0;

  while (*cur) {
    pass_spaces(&cur);
    if (!*cur) break;

    if (isdigit((unsigned char)*cur) || *cur == '.') {
      out[n++] = extract_num(&cur);
    } else if (strchr("+-*/", *cur)) {
      out[n++] = extract_op(&cur);
    } else {
      fprintf(stderr, "Lexer error: '%c' unknown.\n", *cur);
      cur++;
    }
  }

  Token end = {TOKEN_EOF, "EOF"};
  out[n++] = end;
  return n;
}
