#include "boxes.h"
#include "utility_classes.h"

void init_boxes_classes() {
  add_util_class("float-start", ".%s {float: inline-start;}",
                 SINGLE_REPLACEMENT);
  add_util_class("!float-start", ".%s {float: inline-start !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("float-end", ".%s {float: inline-end;}", SINGLE_REPLACEMENT);
  add_util_class("!float-end", ".%s {float: inline-end !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("float-right", ".%s {float: right;}", SINGLE_REPLACEMENT);
  add_util_class("!float-right", ".%s {float: right !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("float-left", ".%s {float: left;}", SINGLE_REPLACEMENT);
  add_util_class("!float-left", ".%s {float: left !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("float-none", ".%s {float: none;}", SINGLE_REPLACEMENT);
  add_util_class("!float-none", ".%s {float: none !important;}",
                 SINGLE_REPLACEMENT);
}
