#ifndef _ARRAYS_H
#define _ARRAYS_H

#include "types.h"
#include <stdbool.h>
#include <stdlib.h>

#define ARRAYS_OK 0
#define ARRAYS_OUT_OF_BOUND 1
#define ARRAYS_INVALID_TYPE 2
#define ARRAYS_MEMORY_ERROR 3

typedef char none;

#ifndef NONE
#define NONE 69
#endif // NONE

typedef enum {
  INTS32,
  DOUBLES,
  STRINGS,
  PAIRS,
} array_type;

typedef union {
  none none; // none type to indicate invalid item
  const int *int32;
  const double *float64;
  char *string;
  const pair *pair;
} array_item;

typedef struct {
  size_t cap;
  size_t len;
  // TODO: change to const
  array_type type;
  array_item *items;
} array;

array *array_new(size_t size, array_type type);
void array_destroy(array *a);
void array_shallow_destroy(array *a);
array_item array_at(array *a, size_t idx);
int array_set_int32_at(array *a, size_t idx, const int item);
int array_set_double_at(array *a, size_t idx, double item);
int array_set_string_at(array *a, size_t idx, const char *item);
int array_set_pair_at(array *a, size_t idx, const pair *item);
int array_push_pair(array *a, const pair *item);
bool array_is_item_none(array_item item);

#ifndef ARRAY_ITER
#define ARRAY_ITER(a, it)                                                      \
  for (array_item it =                                                         \
           (a->len > 0 ? array_at(a, 0) : (array_item){.none = 69});           \
       it.none != 69; it = (array_item){.none = 69})                           \
    for (size_t i = 0; i < a->len; it = array_at(a, ++i))
#endif // ARRAY_ITER

#endif // _ARRAYS_H
