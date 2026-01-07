#include "parseur.h"
#include <stdio.h>
#include <stdlib.h>

static ASTNode *alloc_node_num(double v) {
  ASTNode *n = calloc(1, sizeof(ASTNode));
  if(!n) exit(1);
  n->type = NODE_NUMBER;
  n->value = v;
  return n;
}

static ASTNode *alloc_node_op(char op, ASTNode *l, ASTNode *r) {
  ASTNode *n = calloc(1, sizeof(ASTNode));
  if(!n) exit(1);
  n->type = NODE_OPERATOR;
  n->op.operator = op;
  n->op.left = l;
  n->op.right = r;
  return n;
}

ASTNode *parse_tokens(Token *toks, int count) {
  // Simple parser expecting NUM OP NUM
  if (count > 0 && toks[count - 1].type == TOKEN_EOF) count--;

  if (count < 3) {
    fprintf(stderr, "Parsing error: too short.\n");
    exit(1);
  }

  if (toks[0].type == TOKEN_NUMBER && toks[2].type == TOKEN_NUMBER && toks[1].type == TOKEN_OPERATOR) {
    return alloc_node_op(toks[1].value[0], alloc_node_num(atof(toks[0].value)), alloc_node_num(atof(toks[2].value)));
  }

  fprintf(stderr, "Parsing error: pattern fail.\n");
  exit(1);
}

void free_ast(ASTNode *n) {
  if (!n) return;
  if (n->type == NODE_OPERATOR) {
    free_ast(n->op.left);
    free_ast(n->op.right);
  }
  free(n);
}
