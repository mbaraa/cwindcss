#include "position_placing.h"
#include "utility_classes.h"

void init_position_placing_classes() {
  add_util_class("static", ".%s {position: static;}", NO_REPLACEMENT);
  add_util_class("!static", ".%s {position: static !important;}",
                 NO_REPLACEMENT);
  add_util_class("fixed", ".%s {position: fixed;}", NO_REPLACEMENT);
  add_util_class("!fixed", ".%s {position: fixed !important;}", NO_REPLACEMENT);
  add_util_class("absolute", ".%s {position: absolute;}", NO_REPLACEMENT);
  add_util_class("!absolute", ".%s {position: absolute !important;}",
                 NO_REPLACEMENT);
  add_util_class("relative", ".%s {position: relative;}", NO_REPLACEMENT);
  add_util_class("!relative", ".%s {position: relative !important;}",
                 NO_REPLACEMENT);
  add_util_class("sticky", ".%s {position: sticky;}", NO_REPLACEMENT);
  add_util_class("!sticky", ".%s {position: sticky !important;}",
                 NO_REPLACEMENT);
}
