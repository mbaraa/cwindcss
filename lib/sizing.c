#include "sizing.h"
#include "arrays.h"
#include "css.h"
#include "utility_classes.h"
#include <stdio.h>

void init_sizing_classes() {
  // free ballling
  array *matcher_css_pairs = array_new(0, PAIRS);
  array *tmp = NULL;
  int stat = 0;

  tmp = get_class_and_fmt_variations("w", "width", "%s",
                                     NORMAL | NEGATIVE | IMPORTANT);

  ARRAY_ITER(tmp, it) { array_push_pair(matcher_css_pairs, it.pair); }
  array_shallow_destroy(tmp);
  tmp = get_class_and_fmt_variations("h", "height", "%s",
                                     NORMAL | NEGATIVE | IMPORTANT);
  ARRAY_ITER(tmp, it) { array_push_pair(matcher_css_pairs, it.pair); }
  array_shallow_destroy(tmp);
  tmp = get_class_and_fmt_variations("max-w", "max-width", "%s",
                                     NORMAL | NEGATIVE | IMPORTANT);
  ARRAY_ITER(tmp, it) { array_push_pair(matcher_css_pairs, it.pair); }
  array_shallow_destroy(tmp);
  tmp = get_class_and_fmt_variations("min-w", "min-width", "%s",
                                     NORMAL | NEGATIVE | IMPORTANT);
  ARRAY_ITER(tmp, it) { array_push_pair(matcher_css_pairs, it.pair); }
  array_shallow_destroy(tmp);
  tmp = get_class_and_fmt_variations("max-h", "max-height", "%s",
                                     NORMAL | NEGATIVE | IMPORTANT);
  ARRAY_ITER(tmp, it) { array_push_pair(matcher_css_pairs, it.pair); }
  array_shallow_destroy(tmp);
  tmp = get_class_and_fmt_variations("min-h", "min-height", "%s",
                                     NORMAL | NEGATIVE | IMPORTANT);
  ARRAY_ITER(tmp, it) { array_push_pair(matcher_css_pairs, it.pair); }

  // predefined
  add_util_class("w-24", ".w-24 {width: 92px;}", NO_REPLACEMENT);

  // hmm
  ARRAY_ITER(matcher_css_pairs, it) {
    add_util_class(it.pair->strstr->first, it.pair->strstr->second,
                   SINGLE_REPLACEMENT);
    pair_destroy((pair *)it.pair);
  }

  array_shallow_destroy(tmp);
  array_shallow_destroy(matcher_css_pairs);
}
