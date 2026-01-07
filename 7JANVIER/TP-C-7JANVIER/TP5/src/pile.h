#ifndef PILE_H
#define PILE_H

void infix_to_postfix(const char *in, char *out);
double evaluate_postfix(char *postfix);
void process_infix(char *input); // renamed from traiter

#endif
