#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void skip_whitespace(const char **input) {
  if (input == NULL || *input == NULL)
    return;
  while (isspace((unsigned char)**input)) {
    (*input)++;
  }
}

Token get_number(const char **input) {
  Token token;
  token.type = TOKEN_NUMBER;
  int index = 0;
  const int maxlen = (int)sizeof(token.value) - 1;
  int dot_count = 0;

  if (input == NULL || *input == NULL) {
    token.type = TOKEN_UNKNOWN;
    token.value[0] = '\0';
    return token;
  }

  while ((**input != '\0') &&
         (isdigit((unsigned char)**input) || **input == '.')) {
    if (**input == '.') {
      dot_count++;
      if (dot_count > 1)
        break; // nombre invalide avec plusieurs points
    }
    if (index < maxlen) {
      token.value[index++] = **input;
    }
    (*input)++;
  }
  token.value[index] = '\0';
  return token;
}

Token get_operator(const char **input) {
  Token token;
  token.type = TOKEN_OPERATOR;
  token.value[0] = '\0';
  if (input == NULL || *input == NULL || **input == '\0') {
    token.type = TOKEN_UNKNOWN;
    return token;
  }
  token.value[0] = **input;
  token.value[1] = '\0';
  (*input)++;
  return token;
}

// Fonction principale pour tokeniser l'entrée
int tokenize(const char *input, Token *output) {
  const char *current = input;
  int token_count = 0;

  while (*current != '\0') { // Tant qu'on n'a pas atteint la fin de la chaîne
    skip_whitespace(&current);

    if (*current == '\0')
      break;

    if (isdigit((unsigned char)*current) || *current == '.') {
      // Tokeniser un nombre
      output[token_count++] = get_number(&current);
    } else if (*current == '+' || *current == '-' || *current == '*' ||
               *current == '/') {
      // Tokeniser un opérateur
      output[token_count++] = get_operator(&current);
    } else {
      // Gérer les erreurs de syntaxe (caractère inconnu)
      fprintf(stderr, "Unknown token: %c\n", *current);
      current++;
    }
  }

  // Ajouter un token de fin de fichier (EOF)
  Token eof_token;
  eof_token.type = TOKEN_EOF;
  strcpy(eof_token.value, "EOF");
  output[token_count++] = eof_token;

  // Retourner le nombre de tokens
  return token_count;
}
