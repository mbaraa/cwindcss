#include "positioning.h"
#include "utility_classes.h"

void init_positioning_classes() {
  add_util_class("top", ".%s {top: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!top", ".%s {top: %s !important;}", SINGLE_REPLACEMENT);
  add_util_class("-top", ".%s {top: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("right", ".%s {right: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!right", ".%s {right: %s !important;}", SINGLE_REPLACEMENT);
  add_util_class("-right", ".%s {right: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("bottom", ".%s {bottom: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!bottom", ".%s {bottom: %s !important;}", SINGLE_REPLACEMENT);
  add_util_class("-bottom", ".%s {bottom: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("left", ".%s {left: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!left", ".%s {left: %s !important;}", SINGLE_REPLACEMENT);
  add_util_class("-left", ".%s {left: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("z", ".%s {z-index: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!z", ".%s {z-index: %s !important;}", SINGLE_REPLACEMENT);
  add_util_class("-z", ".%s {z-index: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("inset", ".%s {inset: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!inset", ".%s {inset: %s !important;}", SINGLE_REPLACEMENT);
  add_util_class("-inset", ".%s {inset: -%s;}", SINGLE_REPLACEMENT);
}
