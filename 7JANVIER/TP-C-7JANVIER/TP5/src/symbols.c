#include "symbols.h"

Entry table[TBL_MAX];

void sym_init() {
  for (int i = 0; i < TBL_MAX; i++) table[i].used = 0;
}

int sym_put(const char *key, Value val) {
  // Update existing
  for (int i = 0; i < TBL_MAX; i++) {
    if (table[i].used && strcmp(table[i].id, key) == 0) {
      if (table[i].v.kind != val.kind) {
        fprintf(stderr, "Type mismatch for %s\n", key);
        return -1;
      }
      if (table[i].v.kind == T_STR) free(table[i].v.val.s);
      table[i].v = val;
      return 0;
    }
  }
  // Create new
  for (int i = 0; i < TBL_MAX; i++) {
    if (!table[i].used) {
      strncpy(table[i].id, key, VAR_MAX);
      table[i].v = val;
      table[i].used = 1;
      return 0;
    }
  }
  return -1;
}

int sym_get(const char *key, Value *out) {
  for (int i = 0; i < TBL_MAX; i++) {
    if (table[i].used && strcmp(table[i].id, key) == 0) {
      *out = table[i].v;
      return 0;
    }
  }
  return -1;
}

void sym_print(const char *key) {
  Value v;
  if(sym_get(key, &v) == 0) {
    if(v.kind == T_INT) printf("%d (int)\n", v.val.i);
    else if(v.kind == T_REAL) printf("%g (real)\n", v.val.f);
    else if(v.kind == T_STR) printf("\"%s\" (string)\n", v.val.s);
  } else {
    printf("Err: %s unknown\n", key);
  }
}
