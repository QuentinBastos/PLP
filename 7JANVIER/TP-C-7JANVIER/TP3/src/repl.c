#include "evaluation.h"
#include "lexer.h"
#include "parseur.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
  char key[64];
  void (*handler)(char *args, char *lang);
  char lang[4];
  bool has_arg;
} Cmd;

// Prototypes
void cmd_version(char *a, char *l);
void cmd_help(char *a, char *l);
void cmd_exit(char *a, char *l);
void cmd_echo(char *a, char *l);
void cmd_date(char *a, char *l);

// Liste des commandes
Cmd liste_cmd[] = {
    {"version", cmd_version, "fr", false},
    {"aide", cmd_help, "fr", false},
    {"help", cmd_help, "en", false},
    {"quitter", cmd_exit, "fr", false},
    {"quit", cmd_exit, "en", false},
    {"afficher ", cmd_echo, "fr", true},
    {"echo ", cmd_echo, "en", true},
    {"date", cmd_date, "fr", false},
    {"now", cmd_date, "en", false}
};
size_t nb_cmds = sizeof(liste_cmd) / sizeof(Cmd);
int running = 1;

void to_lower_case(char *s) {
  for (; *s; ++s) *s = tolower((unsigned char)*s);
}

void process_expr(char *input, char *l) {
  // Alloue dynamiquement le buffer de tokens
  Token *toks = calloc(64, sizeof(Token));
  if (!toks) return;

  int count = tokenize(input, toks);
  ASTNode *root = parse_tokens(toks, count);
  double res = evaluate_expression(root);

  if (strcmp(l, "fr") == 0) printf("Résultat : %g\n", res);
  else printf("Result : %g\n", res);

  free(toks);
  free_ast(root);
}

void dispatch(char *raw_cmd, Cmd *params, size_t n, char *def_lang) {
  char buffer[1024];
  strcpy(buffer, raw_cmd);
  to_lower_case(buffer);

  for (size_t i = 0; i < n; i++) {
    size_t sz = strlen(params[i].key);
    if (!sz) continue;

    if (strncmp(buffer, params[i].key, sz) == 0) {
      params[i].handler(raw_cmd, params[i].lang);
      return;
    }
  }

  char *p = buffer;
  while(isspace((unsigned char)*p)) p++;

  // Si pas de commande, peut-être une expression ?
  if (*p && (isdigit((unsigned char)*p) || *p == '(')) {
    process_expr(raw_cmd, "fr"); // Default to FR for TP3
    return;
  }

  printf("Commande inconnue : %s\n", raw_cmd);
}

void cmd_version(char *a, char *l) {
  printf("Ver: %s (GCC %d.%d)\n", strcmp(l,"fr")==0 ? "TP3" : "TP3-EN", __GNUC__, __GNUC_MINOR__);
}

void cmd_help(char *a, char *l) {
  printf("%s:\n", strcmp(l,"fr")==0 ? "Aide" : "Help");
  for(size_t i=0; i<nb_cmds; i++) {
    printf("- %s\n", liste_cmd[i].key);
  }
}

void cmd_exit(char *a, char *l) {
  printf("%s\n", strcmp(l,"fr")==0 ? "Bye." : "Exit.");
  running = 0;
}

void cmd_echo(char *a, char *l) {
  int offset = (strcmp(l,"fr")==0) ? 9 : 5;
  printf("ECHO: %s\n", a + offset);
}

void cmd_date(char *a, char *l) {
  time_t t = time(0);
  struct tm *now = localtime(&t);
  printf("%02d/%02d/%d %02d:%02d\n", now->tm_mday, now->tm_mon+1, now->tm_year+1900, 
         now->tm_hour, now->tm_min);
}

int main(void) {
  char buf[1024];
  while(running) {
    printf("TP3> ");
    if(!fgets(buf, sizeof(buf), stdin)) break;
    buf[strcspn(buf, "\n")] = 0; // Strip newline
    if(!*buf) continue;

    dispatch(buf, liste_cmd, nb_cmds, NULL);
  }
  return 0;
}