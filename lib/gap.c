#include "gap.h"
#include "utility_classes.h"

void init_gap_classes() {
  add_util_class("gap", ".%s {gap: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!gap", ".%s {gap: %s !important;}", SINGLE_REPLACEMENT);
}
