#include "parseur.h"
#include <stdio.h>
#include <stdlib.h>

// Helper pour allouer un nombre
static ASTNode *make_num(double val) {
  ASTNode *n = malloc(sizeof(ASTNode));
  if (!n) {
    perror("Alloc error");
    exit(1);
  }
  n->type = NODE_NUMBER;
  n->value = val;
  return n;
}

// Helper pour allouer un opérateur
static ASTNode *make_op(char op, ASTNode *gauche, ASTNode *droite) {
  ASTNode *n = malloc(sizeof(ASTNode));
  if (!n) {
    perror("Alloc error");
    exit(1);
  }
  n->type = NODE_OPERATOR;
  n->op.operator = op;
  n->op.left = gauche;
  n->op.right = droite;
  return n;
}

ASTNode *parse_tokens(Token *tokens, int len) {
  if (len <= 0) {
    fprintf(stderr, "Pas de tokens à analyser.\n");
    exit(1);
  }

  // Ignore EOF à la fin
  if (tokens[len - 1].type == TOKEN_EOF) {
    len--;
  }

  if (len < 3) {
    fprintf(stderr, "Expression trop courte (min 3 items).\n");
    exit(1);
  }

  // Structure attendue : NOMBRE OP NOMBRE
  Token t1 = tokens[0];
  Token t2 = tokens[1];
  Token t3 = tokens[2];

  if (t1.type != TOKEN_NUMBER || t3.type != TOKEN_NUMBER || t2.type != TOKEN_OPERATOR) {
    fprintf(stderr, "Syntaxe incorrecte (attendu: NB OP NB).\n");
    exit(1);
  }

  double v1 = atof(t1.value);
  double v2 = atof(t3.value);

  return make_op(t2.value[0], make_num(v1), make_num(v2));
}

void free_ast(ASTNode *node) {
  if (!node) return;

  if (node->type == NODE_OPERATOR) {
    free_ast(node->op.left);
    free_ast(node->op.right);
  }
  free(node);
}
