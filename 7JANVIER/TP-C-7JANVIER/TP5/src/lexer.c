#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void pass_spaces(const char **p) {
  if (!p || !*p) return;
  while (isspace(**p)) (*p)++;
}

Token extract_num(const char **p) {
  Token t; t.type = TOKEN_NUMBER;
  int i=0;
  for(;**p;(*p)++) {
      if(!isdigit(**p) && **p!='.') break;
      if(i<63) t.value[i++]=**p;
  }
  t.value[i]=0;
  return t;
}

Token extract_op(const char **p) {
  Token t; t.type = TOKEN_OPERATOR;
  t.value[0]=**p; t.value[1]=0;
  (*p)++;
  return t;
}

int tokenize(const char *in, Token *out) {
  const char *cur = in;
  int n = 0;
  while (*cur) {
      pass_spaces(&cur);
      if(!*cur) break;
      if(isdigit(*cur) || *cur=='.') out[n++] = extract_num(&cur);
      else if (strchr("+-*/", *cur)) out[n++] = extract_op(&cur);
      else cur++;
  }
  Token end = { TOKEN_EOF, "EOF" };
  out[n++] = end;
  return n;
}
