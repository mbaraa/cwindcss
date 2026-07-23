#include "boxes.h"
#include "arrays.h"
#include "css.h"
#include "utility_classes.h"

void init_boxes_classes() {
  array *matcher_css_pairs = array_new(0, PAIRS);
  array *tmp = NULL;

  tmp = get_class_and_fmt_variations("float-start", "float", "inline-start",
                                     NORMAL | IMPORTANT);
  ARRAY_ITER(tmp, it) { array_push_pair(matcher_css_pairs, it.pair); }
  array_shallow_destroy(tmp);
  tmp = get_class_and_fmt_variations("float-end", "float", "inline-end ",
                                     NORMAL | IMPORTANT);
  ARRAY_ITER(tmp, it) { array_push_pair(matcher_css_pairs, it.pair); }
  array_shallow_destroy(tmp);
  tmp = get_class_and_fmt_variations("float-right", "float", "right",
                                     NORMAL | IMPORTANT);
  ARRAY_ITER(tmp, it) { array_push_pair(matcher_css_pairs, it.pair); }
  array_shallow_destroy(tmp);
  tmp = get_class_and_fmt_variations("float-left", "float", "left",
                                     NORMAL | IMPORTANT);
  ARRAY_ITER(tmp, it) { array_push_pair(matcher_css_pairs, it.pair); }
  array_shallow_destroy(tmp);
  tmp = get_class_and_fmt_variations("float-none", "float", "none",
                                     NORMAL | IMPORTANT);
  ARRAY_ITER(tmp, it) { array_push_pair(matcher_css_pairs, it.pair); }

  ARRAY_ITER(matcher_css_pairs, it) {
    add_util_class(it.pair->strstr->first, it.pair->strstr->second,
                   SINGLE_REPLACEMENT);
    pair_destroy((pair *)it.pair);
  }

  array_shallow_destroy(tmp);
  array_shallow_destroy(matcher_css_pairs);
}
