#include "arrays.h"
#include <stdio.h>
#include <string.h>

array *array_new(size_t size, array_type type) {
  array *a = (array *)malloc(sizeof(array));
  a->type = type;
  a->len = size;
  a->items = (array_item *)malloc(sizeof(array_item) * size);

  memset(a->items, 0, size);

  return a;
}

void array_destroy(array *a) {
  for (size_t i = 0; i < a->len; i++) {
    if (a->type == STRINGS) {
      free((void *)a->items[i].string);
    }
    if (a->type == PAIRS) {
      pair_destroy((pair *)a->items[i].pair);
    }
  }
  free(a->items);
  free(a);
}

array_item array_at(array *a, size_t idx) {
  array_item item;
  item.none = NONE;

  if (idx > a->len || idx < 0 ||
      (a->type == STRINGS && a->items[idx].string == NULL)) {
    return item;
  }

  return a->items[idx];
}

int assert_index_and_type(array *a, size_t idx, array_type type) {
  if (idx >= a->len || idx < 0) {
    return ARRAYS_OUT_OF_BOUND;
  }
  if (a->type != type) {
    return ARRAYS_INVALID_TYPE;
  }

  return ARRAYS_OK;
}

int array_set_int32_at(array *a, size_t idx, int item) {
  int stat = assert_index_and_type(a, idx, INTS32);
  if (stat != ARRAYS_OK) {
    return stat;
  }

  const int *ptr = &item;
  a->items[idx] = (array_item){.int32 = ptr};
  return ARRAYS_OK;
}

int array_set_double_at(array *a, size_t idx, double item) {
  int stat = assert_index_and_type(a, idx, DOUBLES);
  if (stat != ARRAYS_OK) {
    return stat;
  }

  const double *ptr = &item;
  a->items[idx] = (array_item){.float64 = ptr};
  return ARRAYS_OK;
}

int array_set_string_at(array *a, size_t idx, const char *item) {
  int stat = assert_index_and_type(a, idx, STRINGS);
  if (stat != ARRAYS_OK) {
    return stat;
  }

  a->items[idx] = (array_item){.string = (char *)item};
  return ARRAYS_OK;
}

int array_set_pair_at(array *a, size_t idx, const pair *item) {
  int stat = assert_index_and_type(a, idx, PAIRS);
  if (stat != ARRAYS_OK) {
    return stat;
  }

  a->items[idx] = (array_item){.pair = item};
  return ARRAYS_OK;
}

int array_set_at(array *a, size_t idx, array_item item) {
  if (idx >= a->len || idx < 0) {
    return ARRAYS_OUT_OF_BOUND;
  }

  a->items[idx] = item;
  return ARRAYS_OK;
}

bool array_is_item_none(array_item item) { return item.none == NONE; }
