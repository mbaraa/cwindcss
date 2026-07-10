#include "tables.h"
#include "utility_classes.h"

void init_tables_classes() {
  add_util_class("table-auto", ".%s {table-layout: auto;}", SINGLE_REPLACEMENT);
  add_util_class("!table-auto", ".%s {table-layout: auto !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("table-fixed", ".%s {table-layout: fixed;}",
                 SINGLE_REPLACEMENT);
  add_util_class("!table-fixed", ".%s {table-layout: fixed !important;}",
                 SINGLE_REPLACEMENT);
}
