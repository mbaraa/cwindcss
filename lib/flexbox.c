#include "flexbox.h"
#include "utility_classes.h"

void init_flexbox_classes() {
  add_util_class("flex-row", ".%s {flex-direction: row;}", NO_REPLACEMENT);
  add_util_class("!flex-row", ".%s {flex-direction: row !important;}",
                 NO_REPLACEMENT);
  add_util_class("flex-row-reverse", ".%s {flex-direction: row-reverse;}",
                 NO_REPLACEMENT);
  add_util_class("!flex-row-reverse",
                 ".%s {flex-direction: row-reverse !important;}",
                 NO_REPLACEMENT);
  add_util_class("flex-col", ".%s {flex-direction: col;}", NO_REPLACEMENT);
  add_util_class("!flex-col", ".%s {flex-direction: col !important;}",
                 NO_REPLACEMENT);
  add_util_class("flex-col-reverse", ".%s {flex-direction: column-reverse;}",
                 NO_REPLACEMENT);
  add_util_class("!flex-col-reverse",
                 ".%s {flex-direction: column-reverse !important;}",
                 NO_REPLACEMENT);
  add_util_class("flex-wrap", ".%s {flex-wrap: wrap;}", NO_REPLACEMENT);
  add_util_class("!flex-wrap", ".%s {flex-wrap: wrap !important;}",
                 NO_REPLACEMENT);
  add_util_class("flex-wrap-reverse", ".%s {flex-wrap: wrap-reverse;}",
                 NO_REPLACEMENT);
  add_util_class("!flex-wrap-reverse",
                 ".%s {flex-wrap: wrap-reverse !important;}", NO_REPLACEMENT);
  add_util_class("flex-nowrap", ".%s {flex-wrap: nowrap;}", NO_REPLACEMENT);
  add_util_class("!flex-nowrap", ".%s {flex-wrap: nowrap !important;}",
                 NO_REPLACEMENT);
  add_util_class("grow", ".%s {flex-grow: 1;}", NO_REPLACEMENT);
  add_util_class("!grow", ".%s {flex-grow: 1 !important;}", NO_REPLACEMENT);
  add_util_class("grow-0", ".%s {flex-grow: 1;}", NO_REPLACEMENT);
  add_util_class("!grow-0", ".%s {flex-grow: 1 !important;}", NO_REPLACEMENT);
  add_util_class("shrink", ".%s {flex-shrink: 1;}", NO_REPLACEMENT);
  add_util_class("!shrink", ".%s {flex-shrink: 1 !important;}", NO_REPLACEMENT);
  add_util_class("shrink-0", ".%s {flex-shrink: 0;}", NO_REPLACEMENT);
  add_util_class("!shrink-0", ".%s {flex-shrink: 0 !important;}",
                 NO_REPLACEMENT);
}
