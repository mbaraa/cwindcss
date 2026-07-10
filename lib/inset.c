#include "inset.h"
#include "utility_classes.h"

void init_inset_classes() {
  add_util_class("inset-x", ".%s {left: %s; right: %s;}", DOUBLE_REPLACEMENT);
  add_util_class("!inset-x", ".%s {left: %s !important; right: %s !important;}",
                 DOUBLE_REPLACEMENT);
  add_util_class("-inset-x", ".%s {left: -%s; right: -%s;}",
                 DOUBLE_REPLACEMENT);
  add_util_class("inset-y", ".%s {top: %s; bottom: %s;}", DOUBLE_REPLACEMENT);
  add_util_class("!inset-y", ".%s {top: %s !important; bottom: %s !important;}",
                 DOUBLE_REPLACEMENT);
  add_util_class("-inset-y", ".%s {top: -%s; bottom: -%s;}",
                 DOUBLE_REPLACEMENT);
}
