#include "evaluation.h"
#include <stdio.h>
#include <stdlib.h>

double evaluate_expression(ASTNode *root) {
  if (!root) return 0;
  
  if (root->type == NODE_NUMBER) return root->value;
  
  if (root->type == NODE_OPERATOR) {
    double l = evaluate_expression(root->op.left);
    double r = evaluate_expression(root->op.right);
    switch(root->op.operator) {
      case '+': return l + r;
      case '-': return l - r;
      case '*': return l * r;
      case '/': return (r != 0) ? l / r : 0; // Avoid crash
    }
  }
  return 0;
}