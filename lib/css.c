#include "css.h"
#include "arrays.h"
#include "types.h"
#include <stdio.h>
#include <string.h>

#define VARIATION_ITER(it)                                                     \
  for (variations_t it = NORMAL; it <= IMPORTANT; it <<= 1)

int count_variations(variations_t variations) {
  int count = 0;
  VARIATION_ITER(v) {
    if (variations & v) {
      count++;
    }
  }

  return count;
}

array *get_class_and_fmt_variations(char *class_matcher, char *property_name,
                                    char *property_value,
                                    variations_t variations) {
  int vc = count_variations(variations);
  array *output = array_new(vc, PAIRS);

  size_t class_matcher_len = strlen(class_matcher);

  size_t i = 0;
  VARIATION_ITER(v) {
    if (!(variations & v)) {
      continue;
    }

    char *class_name = NULL;
    char *pre_fmt = NULL;
    char *fmt = NULL;
    int required_len = 0;

    switch (variations & v) {
    case NORMAL:
      class_name = strdup(class_matcher);
      pre_fmt = ".%%s {%s: %s;}";
      break;
    case NEGATIVE:
      class_name = (char *)malloc(class_matcher_len + 2);
      sprintf(class_name, "-%s", class_matcher);

      pre_fmt = ".%%s {%s: -%s;}";
      break;
    case IMPORTANT:
      class_name = (char *)malloc(class_matcher_len + 2);
      sprintf(class_name, "!%s", class_matcher);

      pre_fmt = ".%%s {%s: %s !important;}";
      break;
    }
    required_len = snprintf(NULL, 0, pre_fmt, property_name, property_value);
    fmt = (char *)malloc(required_len + 1);
    snprintf(fmt, required_len + 1, pre_fmt, property_name, property_value);

    pair *p = pair_new();
    p->strstr->first = class_name;
    p->strstr->second = fmt;
    array_set_pair_at(output, i++, p);
  }

  return output;
}
