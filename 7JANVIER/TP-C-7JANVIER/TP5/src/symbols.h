#ifndef SYMBOLS_H
#define SYMBOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VAR_MAX 64
#define TBL_MAX 100

typedef enum { T_INT, T_REAL, T_STR } ValType;

typedef struct {
  ValType kind;
  union {
    int i;
    double f;
    char *s;
  } val;
} Value;

typedef struct {
  char id[VAR_MAX];
  Value v;
  int used;
} Entry;

void sym_init();
int sym_put(const char *key, Value val);
int sym_get(const char *key, Value *out);
void sym_print(const char *key);

#endif
