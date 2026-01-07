#include "evaluation.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double evaluate_expression(ASTNode *node) {
  if (!node) {
    fprintf(stderr, "Arbre vide.\n");
    exit(1);
  }

  if (node->type == NODE_NUMBER) {
    return node->value;
  }
  
  if (node->type == NODE_OPERATOR) {
    double v_g = evaluate_expression(node->op.left);
    double v_d = evaluate_expression(node->op.right);
    char op = node->op.operator;

    switch (op) {
      case '+': return v_g + v_d;
      case '-': return v_g - v_d;
      case '*': return v_g * v_d;
      case '/': 
        if (v_d == 0) {
          fprintf(stderr, "Division par zero !\n");
          exit(1);
        }
        return v_g / v_d;
      default:
        fprintf(stderr, "Opérateur '%c' non supporté.\n", op);
        exit(1);
    }
  }
  
  return 0;
}