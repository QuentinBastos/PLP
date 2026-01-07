#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Avance le pointeur tant qu'il y a des espaces
void pass_spaces(const char **ptr) {
  if (!ptr || !*ptr) return;
  while (isspace((unsigned char)**ptr)) {
    (*ptr)++;
  }
}

Token extract_num(const char **ptr) {
  Token tok;
  tok.type = TOKEN_NUMBER;
  int i = 0;
  int dot = 0;
  const int limit = (int)sizeof(tok.value) - 1;

  if (!ptr || !*ptr) {
    tok.type = TOKEN_UNKNOWN;
    tok.value[0] = 0;
    return tok;
  }

  // Boucle de lecture
  for (; **ptr != '\0'; (*ptr)++) {
    char c = **ptr;
    if (!isdigit((unsigned char)c) && c != '.') break;

    if (c == '.') {
      dot++;
      if (dot > 1) break; // Trop de points
    }

    if (i < limit) {
      tok.value[i++] = c;
    }
  }
  tok.value[i] = '\0';
  return tok;
}

Token extract_op(const char **ptr) {
  Token tok;
  tok.type = TOKEN_OPERATOR;
  tok.value[0] = 0;

  if (!ptr || !*ptr || !**ptr) {
    tok.type = TOKEN_UNKNOWN;
    return tok;
  }
  
  // Prise de l'opérateur
  tok.value[0] = **ptr;
  tok.value[1] = 0;
  (*ptr)++; // Avance
  return tok;
}

int tokenize(const char *input, Token *output) {
  const char *cursor = input;
  int nb_tok = 0;

  while (*cursor) {
    pass_spaces(&cursor);
    if (!*cursor) break;

    char c = *cursor;
    if (isdigit((unsigned char)c) || c == '.') {
      output[nb_tok++] = extract_num(&cursor);
    } else if (strchr("+-*/", c)) {
      output[nb_tok++] = extract_op(&cursor);
    } else {
      fprintf(stderr, "Erreur lexicale: '%c' inconnu\n", c);
      cursor++;
    }
  }

  // Fin de flux
  Token end;
  end.type = TOKEN_EOF;
  strcpy(end.value, "EOF");
  output[nb_tok++] = end;

  return nb_tok;
}
