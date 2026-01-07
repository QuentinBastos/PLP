#include "evaluation.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double evaluate_expression(ASTNode *root) {
  if (root == NULL) {
    fprintf(stderr, "Erreur: expression invalide (AST nul).\n");
    exit(EXIT_FAILURE);
  }

  if (root->type == NODE_NUMBER) {
    return root->value;
  }

  if (root->type == NODE_OPERATOR) {
    double left_value = evaluate_expression(root->op.left);
    double right_value = evaluate_expression(root->op.right);
    char operator= root->op.operator;

    switch (operator) {
    case '+':
      return left_value + right_value;
    case '-':
      return left_value - right_value;
    case '*':
      return left_value * right_value;
    case '/':
      if (right_value == 0.0) {
        fprintf(stderr, "Erreur: division par zéro.\n");
        exit(EXIT_FAILURE);
      }
      return left_value / right_value;
    default:
      fprintf(stderr, "Erreur: opérateur inconnu '%c'.\n", operator);
      exit(EXIT_FAILURE);
    }
  }

  fprintf(stderr, "Erreur: nœud AST invalide.\n");
  exit(EXIT_FAILURE);
}