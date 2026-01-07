#ifndef SYMBOLS_H
#define SYMBOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VAR_NAME 64
#define MAX_SYMBOLS 100

typedef enum { TYPE_INT, TYPE_REAL, TYPE_STRING } VarType;

typedef struct {
  VarType type;
  union {
    int i_val;
    double r_val;
    char *s_val;
  } value;
} VarValue;

typedef struct {
  char name[MAX_VAR_NAME];
  VarValue val;
  int is_defined;
} Symbol;

extern Symbol symbol_table[MAX_SYMBOLS];

void init_symbols();
int set_variable(const char *name, VarValue val);
int get_variable(const char *name, VarValue *out_val);
void print_variable(const char *name);

#endif
