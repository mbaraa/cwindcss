#ifndef _TYPES_H
#define _TYPES_H

typedef struct {
  char *first;
  char *second;
} strstr_pair;

typedef struct {
  int first;
  int second;
} intint_pair;

typedef union {
  intint_pair *intint;
  strstr_pair *strstr;
} pair;

pair *pair_new();
void pair_destroy(pair *p);

#endif // _TYPES_H
