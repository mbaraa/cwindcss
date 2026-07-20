#ifndef _CSS_H
#define _CSS_H

#include "arrays.h"

enum variations : unsigned int {
  NORMAL = 1,
  NEGATIVE = 1 << 1,
  IMPORTANT = 1 << 2,
};

typedef unsigned int variations_t;

array *get_class_and_fmt_variations(char *class_matcher, char *property_name,
                                    char *property_value,
                                    variations_t variations);
#endif // _CSS_H
