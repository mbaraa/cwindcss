#ifndef _TYPES_H
#define _TYPES_H

typedef struct {
  char *first;
  char *second;
} strstr_pair;

typedef union {
  strstr_pair *strstr;
} pair;

void pair_destroy(pair *p);

#endif // _TYPES_H
