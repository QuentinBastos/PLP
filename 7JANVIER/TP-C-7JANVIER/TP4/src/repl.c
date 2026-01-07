#include "evaluation.h"
#include "lexer.h"
#include "parseur.h"
#include "pile.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
  char key[32];
  void (*cb)(char *args, char *lang);
  char l[4];
  bool arg;
} Action;

void cb_ver(char *a, char *l);
void cb_hlp(char *a, char *l);
void cb_bye(char *a, char *l);
void cb_prt(char *a, char *l);
void cb_now(char *a, char *l);

Action list[] = {
    {"version", cb_ver, "fr", false},
    {"aide", cb_hlp, "fr", false},
    {"help", cb_hlp, "en", false},
    {"quitter", cb_bye, "fr", false},
    {"quit", cb_bye, "en", false},
    {"afficher ", cb_prt, "fr", true},
    {"echo ", cb_prt, "en", true},
    {"date", cb_now, "fr", false},
    {"now", cb_now, "en", false}
};
size_t nb = sizeof(list) / sizeof(Action);
int active = 1;

void str_lower(char *s) {
  for (; *s; ++s) *s = tolower((unsigned char)*s);
}

void process_line(char *line, Action *acts, size_t count) {
  char buf[1024];
  strcpy(buf, line);
  str_lower(buf);

  for (size_t i = 0; i < count; i++) {
    size_t len = strlen(acts[i].key);
    if (!len) continue;
    if (strncmp(buf, acts[i].key, len) == 0) {
      acts[i].cb(line, acts[i].l);
      return;
    }
  }

  // Fallback: Expression
  if (*buf && (isdigit((unsigned char)*buf) || *buf == '(')) {
    handle_infix_expr(line); // Changed name here
    return;
  }

  printf("Cmd inconnue: %s\n", line);
}

void cb_ver(char *a, char *l) {
  printf(strcmp(l,"fr")==0 ? "TP4 Version:\n" : "TP4 Release:\n");
  printf("GCC %d.%d\n", __GNUC__, __GNUC_MINOR__);
}

void cb_bye(char *a, char *l) {
  printf(strcmp(l,"fr")==0 ? "Au revoir.\n" : "Goodbye.\n");
  active = 0;
}

void cb_prt(char *a, char *l) {
  int off = (strcmp(l,"fr")==0) ? 9 : 5;
  printf("ECHO: %s\n", a + off);
}

void cb_now(char *a, char *l) {
  time_t t = time(0);
  struct tm *now = localtime(&t);
  printf("%d-%02d-%02d %02d:%02d\n", now->tm_year+1900, now->tm_mon+1, now->tm_mday, now->tm_hour, now->tm_min);
}

void cb_hlp(char *a, char *l) {
  printf("Help:\n");
  for(size_t i=0; i<nb; i++) printf(" . %s\n", list[i].key);
}

int main(void) {
  char buf[1024];
  while(active) {
    printf("TP4> ");
    if(!fgets(buf, sizeof(buf), stdin)) break;
    buf[strcspn(buf, "\n")] = 0;
    if(!*buf) continue;
    process_line(buf, list, nb);
    printf("\n");
  }
  return 0;
}