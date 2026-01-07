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

#define MAX_COMMANDS_SIZE 100

typedef struct {
  char name[64];
  void (*function)(char *arg, char *langue);
  char langue[3];
  bool arg;
} Commande;

void afficher_version(char *arg, char *langue);
void afficher_aide(char *arg, char *langue);
void traiter_quit(char *arg, char *langue);
void traiter_echo(char *arg, char *langue);
void date(char *arg, char *langue);
void afficher_message(char *fr, char *en, char *langue);

Commande commandes[] = {{"version", afficher_version, "fr", false},
                        {"aide", afficher_aide, "fr", false},
                        {"help", afficher_aide, "en", false},
                        {"quitter", traiter_quit, "fr", false},
                        {"quit", traiter_quit, "en", false},
                        {"afficher ", traiter_echo, "fr", true},
                        {"echo ", traiter_echo, "en", true},
                        {"date", date, "fr", false},
                        {"now", date, "en", false}};

size_t nb_commande = sizeof(commandes) / sizeof(commandes[0]);
int programme_fini = 1;

void stringToLower(char *str) {
  for (int i = 0; str[i]; i++) {
    str[i] = tolower((unsigned char)str[i]);
  }
}

void replace_all_str(char *str, const char *old, const char *new_str) {
  char buffer[8192];
  char *p;
  while ((p = strstr(str, old))) {
    int len = p - str;
    strncpy(buffer, str, len);
    buffer[len] = '\0';
    strcat(buffer, new_str);
    strcat(buffer, p + strlen(old));
    strcpy(str, buffer);
  }
}

void traiter_expression(char *commande, char *lang) {
  (void)lang;

  // 1. Lambda: (lambda x.expr) arg
  if (strstr(commande, "lambda")) {
    char var_name[64], expr[4096], arg_val[64];
    char *lambda_start = strstr(commande, "lambda");
    char *dot = strchr(lambda_start, '.');
    char *open_paren = strchr(commande, '(');
    char *close_paren = NULL;
    int paren_count = 0;

    if (open_paren) {
      char *current = open_paren;
      while (*current) {
        if (*current == '(')
          paren_count++;
        else if (*current == ')') {
          paren_count--;
          if (paren_count == 0) {
            close_paren = current;
            break;
          }
        }
        current++;
      }
    }

    if (dot && close_paren) {
      // Extract variable name
      strncpy(var_name, lambda_start + 7, dot - (lambda_start + 7));
      var_name[dot - (lambda_start + 7)] = '\0';
      char *saveptr1, *saveptr2;
      char *trimmed_var = strtok_r(var_name, " \t", &saveptr1);

      // Extract expression
      strncpy(expr, dot + 1, close_paren - (dot + 1));
      expr[close_paren - (dot + 1)] = '\0';

      // Extract argument
      strcpy(arg_val, close_paren + 1);
      char *trimmed_arg = strtok_r(arg_val, " \t\r\n", &saveptr2);

      char substitution_val[64] = "";
      VarValue v;
      if (trimmed_arg && isalpha((unsigned char)trimmed_arg[0]) &&
          get_variable(trimmed_arg, &v) == 0) {
        if (v.type == TYPE_INT)
          sprintf(substitution_val, "%d", v.value.i_val);
        else if (v.type == TYPE_REAL)
          sprintf(substitution_val, "%g", v.value.r_val);
        else if (v.type == TYPE_STRING)
          strcpy(substitution_val, v.value.s_val); // Direct string substitution
      } else if (trimmed_arg) {
        strcpy(substitution_val, trimmed_arg);
      }

      if (trimmed_var && substitution_val[0] != '\0') {
        replace_all_str(expr, trimmed_var, substitution_val);
      }
      traiter_expression(expr, lang);
      return;
    }
  }

  // 2. Assignment: var = expr
  char *eq = strchr(commande, '=');
  if (eq) {
    char name[64], expr_part[4096];
    *eq = '\0';
    strcpy(name, commande);
    strcpy(expr_part, eq + 1);
    char *trimmed_name = strtok(name, " \t\r\n");
    char *trimmed_expr = expr_part;
    while (isspace((unsigned char)*trimmed_expr))
      trimmed_expr++;

    VarValue v;
    if (trimmed_expr[0] == '"') {
      v.type = TYPE_STRING;
      char *end_q = strrchr(trimmed_expr + 1, '"');
      if (end_q)
        *end_q = '\0';
      v.value.s_val = strdup(trimmed_expr + 1);
    } else {
      char postfix[4096];
      infix_to_postfix(trimmed_expr, postfix);
      double result = evaluer(postfix);

      if (strchr(trimmed_expr, '.'))
        v.type = TYPE_REAL;
      else
        v.type = TYPE_INT;
      if (v.type == TYPE_INT)
        v.value.i_val = (int)result;
      else
        v.value.r_val = result;
    }

    if (set_variable(trimmed_name, v) == 0) {
      printf("Variable %s définie avec la valeur ", trimmed_name);
      if (v.type == TYPE_INT)
        printf("%d (entier)\n", v.value.i_val);
      else if (v.type == TYPE_REAL)
        printf("%g (nombre réel)\n", v.value.r_val);
      else if (v.type == TYPE_STRING)
        printf("\"%s\" (chaîne de caractères)\n", v.value.s_val);
    }
    return;
  }

  traiter(commande);
}

void taiter(char *cmd, Commande *commandes, size_t nb_commandes, char *langue) {
  (void)langue;
  char commande_lower[1024];
  strcpy(commande_lower, cmd);
  stringToLower(commande_lower);

  for (size_t i = 0; i < nb_commandes; i++) {
    size_t len = strlen(commandes[i].name);
    if (len == 0)
      continue;

    if (strncmp(commande_lower, commandes[i].name, len) == 0) {
      char *lang = commandes[i].langue;
      commandes[i].function(cmd, lang);
      return;
    }
  }

  if (commande_lower[0] != '\0' &&
      (isdigit((unsigned char)commande_lower[0]) || commande_lower[0] == '(' ||
       strchr(commande_lower, '=') ||
       isalpha((unsigned char)commande_lower[0]))) {
    traiter_expression(cmd, "en");
    return;
  }

  printf("Cette commande n'existe pas : %s\n", cmd);
}

void afficher_message(char *fr, char *en, char *langue) {
  printf("%s", strcmp(langue, "fr") == 0 ? fr : en);
}

void afficher_version(char *arg, char *langue) {
  (void)arg;
  afficher_message("Version actuelle de l'interpréteur : \n",
                   "Actual interpretor version: \n", langue);
  printf("GCC %d.%d.%d\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
}

void traiter_quit(char *arg, char *langue) {
  (void)arg;
  afficher_message("Arrêt...\n", "Stopping...\n", langue);
  programme_fini = 0;
}

void traiter_echo(char *arg, char *langue) {
  afficher_message("Affichage : ", "Echo : ", langue);
  int i = strcmp(langue, "fr") == 0 ? 9 : 5;
  for (; arg[i] != '\0'; i++) {
    printf("%c", arg[i]);
  }
  printf("\n"); // Saut de ligne après la sortie
}

void date(char *arg, char *langue) {
  (void)arg;
  afficher_message("Date du jour :\n", "Today date: \n", langue);
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  printf("now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1,
         tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

void afficher_aide(char *arg, char *langue) {
  (void)arg;
  afficher_message("Commandes disponibles : \n", "Available commands: \n",
                   langue);
  for (size_t i = 0; i < nb_commande; i++) {
    printf("Commande : %s \n", commandes[i].name);
  }
}

int main() {
  init_symbols();
  while (programme_fini) {
    printf("> ");

    // Buffer pour stocker la commande utilisateur
    char commande[1024];

    if (fgets(commande, sizeof(commande), stdin) == NULL) {
      break;
    }

    // Enlève le caractère de fin de ligne ajouté par fgets
    commande[strcspn(commande, "\n")] = 0;
    if (commande[0] == '\0') {
      continue;
    }

    taiter(commande, commandes, nb_commande, NULL);

    printf("\n");
  }

  return 0;
}

/*
    Questions à réfléchir

    - Commande echo avec arguments
    -> Il affiche les arguments avec le echo

    - Ajouter des nouvelles commandes
    -> Pour le moment en rajoutant des else if
*/