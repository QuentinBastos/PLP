#include "parseur.h"
#include <stdio.h>
#include <stdlib.h>

static ASTNode *create_number_node(double value) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  if (!node) {
    fprintf(stderr,
            "Erreur: impossible d'allouer de la mémoire pour le nœud AST\n");
    exit(EXIT_FAILURE);
  }
  node->type = NODE_NUMBER;
  node->value = value;
  return node;
}

static ASTNode *create_operator_node(char operator, ASTNode * left,
                                     ASTNode *right) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  if (!node) {
    fprintf(stderr,
            "Erreur: impossible d'allouer de la mémoire pour le nœud AST\n");
    exit(EXIT_FAILURE);
  }
  node->type = NODE_OPERATOR;
  node->op.operator= operator;
  node->op.left = left;
  node->op.right = right;
  return node;
}

ASTNode *parse_tokens(Token *tokens, int num_tokens) {
  if (num_tokens <= 0) {
    fprintf(stderr, "Erreur: aucun token reçu pour l'analyse.\n");
    exit(EXIT_FAILURE);
  }

  // Si le dernier token est EOF, l'ignorer pour la vérification de longueur
  if (tokens[num_tokens - 1].type == TOKEN_EOF) {
    num_tokens--;
  }

  if (num_tokens < 3) {
    fprintf(stderr, "Erreur: expression invalide, trop peu de tokens.\n");
    exit(EXIT_FAILURE);
  }

  // Extraction simple : on attend numéro / opérateur / numéro
  Token number1 = tokens[0];
  Token operator= tokens[1];
  Token number2 = tokens[2];

  if (number1.type != TOKEN_NUMBER ||
      number2.type != TOKEN_NUMBER || operator.type != TOKEN_OPERATOR) {
    fprintf(stderr, "Erreur: syntaxe invalide.\n");
    exit(EXIT_FAILURE);
  }

  double value1 = atof(number1.value);
  double value2 = atof(number2.value);

  ASTNode *left_node = create_number_node(value1);
  ASTNode *right_node = create_number_node(value2);
  ASTNode *root =
      create_operator_node(operator.value[0], left_node, right_node);

  return root;
}

void free_ast(ASTNode *node) {
  if (node == NULL) {
    return;
  }

  if (node->type == NODE_OPERATOR) {
    free_ast(node->op.left);
    free_ast(node->op.right);
  }

  free(node);
}
