#include "sizing.h"
#include "utility_classes.h"

void init_sizing_classes() {
  // free ballling
  add_util_class("w", ".%s {width: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!w", ".%s {width: %s !important;}", SINGLE_REPLACEMENT);
  add_util_class("-w", ".%s {width: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("h", ".%s {height: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!h", ".%s {height: %s !important;}", SINGLE_REPLACEMENT);
  add_util_class("-h", ".%s {height: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("max-w", ".%s {max-width: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!max-w", ".%s {max-width: %s !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("-max-w", ".%s {max-width: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("max-h", ".%s {max-height: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!max-h", ".%s {max-height: %s !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("-max-h", ".%s {max-height: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("min-w", ".%s {min-width: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!min-w", ".%s {min-width: %s !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("-min-w", ".%s {min-width: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("min-h", ".%s {min-height: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!min-h", ".%s {min-height: %s !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("-min-h", ".%s {min-height: -%s;}", SINGLE_REPLACEMENT);

  // predefined
  add_util_class("w-24", ".w-24 {width: 92px;}", NO_REPLACEMENT);
}
