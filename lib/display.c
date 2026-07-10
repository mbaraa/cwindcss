#include "display.h"
#include "utility_classes.h"

void init_display_classes() {
  add_util_class("block", ".%s {display: block;}", NO_REPLACEMENT);
  add_util_class("!block", ".%s {display: block !important;}", NO_REPLACEMENT);
  add_util_class("inline-block", ".%s {display: inline-block;}",
                 NO_REPLACEMENT);
  add_util_class("!inline-block", ".%s {display: inline-block !important;}",
                 NO_REPLACEMENT);
  add_util_class("inline", ".%s {display: inline;}", NO_REPLACEMENT);
  add_util_class("!inline", ".%s {display: inline !important;}",
                 NO_REPLACEMENT);
  add_util_class("flex", ".%s {display: flex;}", NO_REPLACEMENT);
  add_util_class("!flex", ".%s {display: flex !important;}", NO_REPLACEMENT);
  add_util_class("grid", ".%s {display: grid;}", NO_REPLACEMENT);
  add_util_class("!grid", ".%s {display: grid !important;}", NO_REPLACEMENT);
  add_util_class("table", ".%s {display: table;}", NO_REPLACEMENT);
  add_util_class("!table", ".%s {display: table !important;}", NO_REPLACEMENT);
  add_util_class("hidden", ".%s {display: none;}", NO_REPLACEMENT);
  add_util_class("!hidden", ".%s {display: none !important;}", NO_REPLACEMENT);
}
