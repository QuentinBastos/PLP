#include "evaluation.h"
#include "lexer.h"
#include "parseur.h"
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

void traiter_expression(char *commande, char *lang) {
  Token *tokens = (Token *)malloc(64 * sizeof(Token));
  int token_count = tokenize(commande, tokens);

  ASTNode *ast = parse_tokens(tokens, token_count);
  double result = evaluate_expression(ast);

  afficher_message("Résultats : ", "Results : ", lang);
  printf("%g\n", result);

  free(tokens);
  free_ast(ast);
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
      (isdigit((unsigned char)commande_lower[0]) || commande_lower[0] == '(')) {
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