#include "arrays.h"
#include <stdio.h>
#include <string.h>

array *array_new(size_t size, array_type type) {
  array *a = (array *)malloc(sizeof(array));
  a->type = type;
  a->len = size;
  a->cap = size * 2;
  size_t items_size = sizeof(array_item) * a->cap;
  a->items = (array_item *)malloc(items_size);

  memset(a->items, 0, items_size);

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

int assert_type(array *a, array_type type) {
  if (a->type != type) {
    return ARRAYS_INVALID_TYPE;
  }

  return ARRAYS_OK;
}

int assert_index_and_type(array *a, size_t idx, array_type type) {
  if (idx >= a->len || idx < 0) {
    return ARRAYS_OUT_OF_BOUND;
  }
  if (assert_type(a, type) != ARRAYS_OK) {
    return ARRAYS_INVALID_TYPE;
  }

  return ARRAYS_OK;
}

int array_set_int32_at(array *a, size_t idx, const int item) {
  int stat = assert_index_and_type(a, idx, INTS32);
  if (stat != ARRAYS_OK) {
    return stat;
  }

  const int *ptr = &item;
  a->items[idx] = (array_item){.int32 = ptr};
  return ARRAYS_OK;
}

int array_resize(array *a) {
  if (a->len < a->cap) {
    return ARRAYS_OK;
  }

  size_t new_cap = (a->cap == 0 ? 1 : a->cap) * 2;
  array_item *new_items = realloc(a->items, new_cap * sizeof(array_item));
  if (new_items == NULL) {
    return ARRAYS_MEMORY_ERROR;
  }

  a->items = new_items;
  a->cap = new_cap;

  return ARRAYS_OK;
}

int array_push_int32(array *a, int item) {
  int stat = assert_type(a, INTS32);
  if (stat != ARRAYS_OK) {
    return stat;
  }

  stat = array_resize(a);
  if (stat != ARRAYS_OK) {
    return stat;
  }

  int item_clone = item;
  int *ptr = &item_clone;
  a->items[a->len++] = (array_item){.int32 = ptr};
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

int array_push_pair(array *a, const pair *item) {
  int stat = assert_type(a, PAIRS);
  if (stat != ARRAYS_OK) {
    return stat;
  }

  stat = array_resize(a);
  if (stat != ARRAYS_OK) {
    return stat;
  }

  a->items[a->len++] = (array_item){.pair = item};
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
