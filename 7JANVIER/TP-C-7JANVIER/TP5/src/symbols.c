#include "symbols.h"

Symbol symbol_table[MAX_SYMBOLS];

void init_symbols() {
  for (int i = 0; i < MAX_SYMBOLS; i++) {
    symbol_table[i].is_defined = 0;
  }
}

int set_variable(const char *name, VarValue val) {
  for (int i = 0; i < MAX_SYMBOLS; i++) {
    if (symbol_table[i].is_defined && strcmp(symbol_table[i].name, name) == 0) {
      if (symbol_table[i].val.type != val.type) {
        fprintf(
            stderr,
            "Erreur : changement de type non autorisé pour la variable %s\n",
            name);
        return -1;
      }
      if (symbol_table[i].val.type == TYPE_STRING)
        free(symbol_table[i].val.value.s_val);
      symbol_table[i].val = val;
      return 0;
    }
  }
  for (int i = 0; i < MAX_SYMBOLS; i++) {
    if (!symbol_table[i].is_defined) {
      strncpy(symbol_table[i].name, name, MAX_VAR_NAME);
      symbol_table[i].val = val;
      symbol_table[i].is_defined = 1;
      return 0;
    }
  }
  return -1;
}

int get_variable(const char *name, VarValue *out_val) {
  for (int i = 0; i < MAX_SYMBOLS; i++) {
    if (symbol_table[i].is_defined && strcmp(symbol_table[i].name, name) == 0) {
      *out_val = symbol_table[i].val;
      return 0;
    }
  }
  return -1;
}

void print_variable(const char *name) {
  VarValue v;
  if (get_variable(name, &v) == 0) {
    if (v.type == TYPE_INT)
      printf("%d (entier)\n", v.value.i_val);
    else if (v.type == TYPE_REAL)
      printf("%g (nombre réel)\n", v.value.r_val);
    else if (v.type == TYPE_STRING)
      printf("\"%s\" (chaîne de caractères)\n", v.value.s_val);
  } else {
    printf("Erreur : la variable %s n'est pas définie\n", name);
  }
}
