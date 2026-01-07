#include "evaluation.h"
#include "lexer.h"
#include "parseur.h"
#include "pile.h"
#include "symbols.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structs
typedef struct {
  char k[64];
  void (*fn)(char *a, char *l);
  char l[4];
  bool arg;
} Cfg;

// Calls
void f_ver(char *a, char *l);
void f_hlp(char *a, char *l);
void f_xit(char *a, char *l);
void f_ech(char *a, char *l);
void f_dat(char *a, char *l);

Cfg cmds[] = {
    {"version", f_ver, "fr", false},
    {"aide", f_hlp, "fr", false},
    {"help", f_hlp, "en", false},
    {"quitter", f_xit, "fr", false},
    {"quit", f_xit, "en", false},
    {"afficher ", f_ech, "fr", true},
    {"echo ", f_ech, "en", true},
    {"date", f_dat, "fr", false},
    {"now", f_dat, "en", false}
};
size_t n_cmds = sizeof(cmds)/sizeof(Cfg);
int keep_running = 1;

void str_sub(char *s, const char *old, const char *rep) {
  char b[8192];
  char *p;
  while ((p = strstr(s, old))) {
    unsigned long len = p - s;
    strncpy(b, s, len);
    b[len] = 0;
    strcat(b, rep);
    strcat(b, p + strlen(old));
    strcpy(s, b);
  }
}

void to_low(char *s) {
  for(;*s;++s) *s = tolower((unsigned char)*s);
}

void handle_logic(char *line, char *lang) {
  // Lambda: (lambda x.expr) arg
  if (strstr(line, "lambda")) {
    char v[64], ex[4096], arg[64];
    char *start = strstr(line, "lambda");
    char *dot = strchr(start, '.');
    char *par = strchr(line, '(');
    char *end = NULL;
    int c = 0;
    
    if (par) {
        char *cur = par;
        while(*cur) {
            if(*cur=='(') c++;
            else if(*cur==')') { c--; if(c==0) { end=cur; break; } }
            cur++;
        }
    }

    if (dot && end) {
        strncpy(v, start+7, dot-(start+7)); v[dot-(start+7)]=0;
        char *ctx;
        char *tv = strtok_r(v, " \t", &ctx);

        strncpy(ex, dot+1, end-(dot+1)); ex[end-(dot+1)]=0;
        
        strcpy(arg, end+1);
        char *ctx2;
        char *ta = strtok_r(arg, " \t\r\n", &ctx2);
        
        char sub[64] = "";
        Value val;
        if (ta && isalpha(ta[0]) && sym_get(ta, &val)==0) {
            if(val.kind == T_INT) sprintf(sub, "%d", val.val.i);
            else if(val.kind == T_REAL) sprintf(sub, "%g", val.val.f);
            else if(val.kind == T_STR) strcpy(sub, val.val.s);
        } else if (ta) {
            strcpy(sub, ta);
        }

        if (tv && sub[0]) str_sub(ex, tv, sub);

        handle_logic(ex, lang);
        return;
    }
  }

  // Assign: x = expr
  char *eq = strchr(line, '=');
  if (eq) {
      char k[64], right[4096];
      *eq = 0;
      strcpy(k, line);
      strcpy(right, eq+1);
      char *tk = strtok(k, " \t\r\n");
      char *te = right;
      while(isspace(*te)) te++;

      Value val;
      if (te[0] == '"') {
          val.kind = T_STR;
          char *eq2 = strrchr(te+1, '"');
          if(eq2) *eq2=0;
          val.val.s = strdup(te+1);
      } else {
          char pf[4096];
          infix_to_postfix(te, pf);
          double r = evaluate_postfix(pf);
          if (strchr(te, '.')) {
            val.kind = T_REAL; val.val.f = r;
          } else {
            val.kind = T_INT; val.val.i = (int)r;
          }
      }

      if (sym_put(tk, val) == 0) {
          printf("Var %s set: ", tk);
          if(val.kind==T_INT) printf("%d\n", val.val.i);
          else if(val.kind==T_REAL) printf("%g\n", val.val.f);
          else printf("'%s'\n", val.val.s);
      }
      return;
  }

  process_infix(line);
}

void run_cmd(char *raw, Cfg *list, size_t n, char *ln) {
  char buf[1024];
  strcpy(buf, raw);
  to_low(buf);

  for(size_t i=0; i<n; i++) {
     size_t l = strlen(list[i].k);
     if(!l) continue;
     if(strncmp(buf, list[i].k, l)==0) {
         list[i].fn(raw, list[i].l);
         return;
     }
  }

  char c = buf[0];
  if (c && (isdigit(c) || c=='(' || strchr(buf,'=') || isalpha(c))) {
      handle_logic(raw, "en");
      return;
  }

  printf("Unknown: %s\n", raw);
}

void msg(char *f, char *e, char *l) { printf("%s", strcmp(l,"fr")==0?f:e); }

void f_ver(char *a, char *l) { msg("Version:\n", "Version:\n", l); printf("GCC %d\n", __GNUC__); }
void f_xit(char *a, char *l) { msg("Fin.\n", "End.\n", l); keep_running = 0; }
void f_ech(char *a, char *l) { msg("Echo: ", "Echo: ", l); printf("%s\n", a + (strcmp(l,"fr")==0?9:5)); }
void f_dat(char *a, char *l) { time_t t=time(0); printf("%s", ctime(&t)); }
void f_hlp(char *a, char *l) { printf("Help:\n"); for(size_t i=0;i<n_cmds;i++) printf("%s\n", cmds[i].k); }

int main() {
  sym_init();
  char buf[1024];
  while(keep_running) {
    printf("TP5> ");
    if(!fgets(buf, 1024, stdin)) break;
    buf[strcspn(buf, "\n")] = 0;
    if(!*buf) continue;
    run_cmd(buf, cmds, n_cmds, NULL);
    printf("\n");
  }
  return 0;
}