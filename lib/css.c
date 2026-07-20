#include "css.h"
#include "arrays.h"
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
  size_t property_name_len = strlen(property_name);
  size_t property_value_len = strlen(property_value);

  size_t i = 0;
  VARIATION_ITER(v) {
    if (!(variations & v)) {
      continue;
    }

    char *class_name = NULL;
    char *fmt = NULL;

    switch (variations & v) {
    case NORMAL:
      class_name = strdup(class_matcher);
      fmt = (char *)malloc(property_name_len + property_value_len + 3 /*.%s*/ +
                           4 /*{} ;*/);
      sprintf(fmt, ".%%s {%s: %s;}", property_name, property_value);
      break;
    case NEGATIVE:
      class_name = (char *)malloc(sizeof(char) * class_matcher_len + 1);
      sprintf(class_name, "-%s", class_matcher);
      fmt = (char *)malloc(property_name_len + property_value_len + 3 /*.%s*/ +
                           5 /*{} ;-*/);
      sprintf(fmt, ".%%s {%s: -%s;}", property_name, property_value);
      break;
    case IMPORTANT:
      class_name = (char *)malloc(sizeof(char) * class_matcher_len + 1);
      sprintf(class_name, "!%s", class_matcher);
      fmt = (char *)malloc(property_name_len + property_value_len + 3 /*.%s*/ +
                           15 /*{} ; !important*/);
      sprintf(fmt, ".%%s {%s: %s !important;}", property_name, property_value);
      break;
    }

    pair *p = pair_new();
    p->strstr->first = class_name;
    p->strstr->second = fmt;
    array_set_pair_at(output, i++, p);
  }

  return output;
}
