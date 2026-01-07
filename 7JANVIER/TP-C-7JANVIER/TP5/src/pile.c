#include "pile.h"
#include "symbols.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SZ 256

typedef struct { char d[SZ]; int n; } SChar;
typedef struct { double d[SZ]; int n; } SNum;

void sc_init(SChar *s) { s->n = -1; }
void sc_push(SChar *s, char c) { if(s->n < SZ-1) s->d[++s->n] = c; }
char sc_pop(SChar *s) { return (s->n >= 0) ? s->d[s->n--] : 0; }
char sc_peek(SChar *s) { return (s->n >= 0) ? s->d[s->n] : 0; }
int sc_empty(SChar *s) { return s->n == -1; }

void sn_init(SNum *s) { s->n = -1; }
void sn_push(SNum *s, double v) { if(s->n < SZ-1) s->d[++s->n] = v; }
double sn_pop(SNum *s) { return (s->n >= 0) ? s->d[s->n--] : 0; }

int get_p(char c) {
  if (strchr("*/%", c)) return 2;
  if (strchr("+-", c)) return 1;
  return 0;
}
int is_o(char c) { return strchr("+-*/%", c) != NULL; }

void norm_str(const char *in, char *out) {
  int x = 0;
  for (int i = 0; in[i]; i++) {
    char c = in[i];
    if (is_o(c) || c=='(' || c==')') {
      out[x++]=' '; out[x++]=c; out[x++]=' ';
    } else {
      out[x++]=c;
    }
  }
  out[x]=0;
}

static int err = 0;

double evaluate_postfix(char *postfix) {
  err = 0;
  SNum s;
  sn_init(&s);
  char tmp[4096];
  strcpy(tmp, postfix);
  char *tok = strtok(tmp, " ");

  while (tok) {
    if (isdigit(tok[0]) || (tok[0]=='-' && isdigit(tok[1]))) {
      sn_push(&s, atof(tok));
    } else if (is_o(tok[0]) && strlen(tok)==1) {
      if (s.n < 1) { err=1; return 0; }
      double b = sn_pop(&s);
      double a = sn_pop(&s);
      switch(tok[0]) {
        case '+': sn_push(&s, a+b); break;
        case '-': sn_push(&s, a-b); break;
        case '*': sn_push(&s, a*b); break;
        case '/': if(b==0) { err=1; sn_push(&s,0); } else sn_push(&s, a/b); break;
        case '%': sn_push(&s, fmod(a,b)); break;
      }
    } else {
      Value v;
      if (sym_get(tok, &v) == 0) {
        if(v.kind == T_INT) sn_push(&s, (double)v.val.i);
        else if(v.kind == T_REAL) sn_push(&s, v.val.f);
      } else {
        // Ignorer ou erreur? "variable non définie"
        err = 1; sn_push(&s, 0);
      }
    }
    tok = strtok(NULL, " ");
  }
  return (s.n == 0) ? sn_pop(&s) : 0;
}

void infix_to_postfix(const char *in, char *out) {
  char n[8192];
  norm_str(in, n);
  SChar s;
  sc_init(&s);
  out[0] = 0;
  
  char *d = strdup(n);
  char *t = strtok(d, " ");
  while(t) {
    if (isdigit(t[0]) || (t[0]=='-' && isdigit(t[1]))) {
      strcat(out, t); strcat(out, " ");
    } else if (t[0]=='(') {
      sc_push(&s, '(');
    } else if (t[0]==')') {
      while(!sc_empty(&s) && sc_peek(&s)!='(') {
        int l=strlen(out); out[l]=sc_pop(&s); out[l+1]=' '; out[l+2]=0;
      }
      sc_pop(&s);
    } else if (is_o(t[0])) {
      while(!sc_empty(&s) && sc_peek(&s)!='(' && get_p(sc_peek(&s)) >= get_p(t[0])) {
        int l=strlen(out); out[l]=sc_pop(&s); out[l+1]=' '; out[l+2]=0;
      }
      sc_push(&s, t[0]);
    } else if (t[0]!='(' && t[0]!=')') {
      strcat(out, t); strcat(out, " ");
    }
    t = strtok(NULL, " ");
  }
  while(!sc_empty(&s)) {
    int l=strlen(out); out[l]=sc_pop(&s); out[l+1]=' '; out[l+2]=0;
  }
  free(d);
}

void process_infix(char *input) {
  char buf[4096];
  infix_to_postfix(input, buf);
  if (strlen(buf)>0) {
    double r = evaluate_postfix(buf);
    if (!err) printf("%g\n", r);
  }
}
