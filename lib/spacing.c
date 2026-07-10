#include "spacing.h"
#include "utility_classes.h"

void init_spacing_classes() {
  add_util_class("p", ".%s {padding: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!p", ".%s {padding: %s !important;}", SINGLE_REPLACEMENT);
  add_util_class("-p", ".%s {padding: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("pt", ".%s {padding-top: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!pt", ".%s {padding-top: %s !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("-pt", ".%s {padding-top: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("pb", ".%s {padding-bottom: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!pb", ".%s {padding-bottom: %s !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("-pb", ".%s {padding-bottom: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("pl", ".%s {padding-left: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!pl", ".%s {padding-left: %s !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("-pl", ".%s {padding-left: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("pr", ".%s {padding-right: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!pr", ".%s {padding-right: %s !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("-pr", ".%s {padding-right: -%s;}", SINGLE_REPLACEMENT);

  add_util_class("m", ".%s {margin: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!m", ".%s {margin: %s !important;}", SINGLE_REPLACEMENT);
  add_util_class("-m", ".%s {margin: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("mt", ".%s {margin-top: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!mt", ".%s {margin-top: %s !important;}", SINGLE_REPLACEMENT);
  add_util_class("-mt", ".%s {margin-top: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("mb", ".%s {margin-bottom: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!mb", ".%s {margin-bottom: %s !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("-mb", ".%s {margin-bottom: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("ml", ".%s {margin-left: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!ml", ".%s {margin-left: %s !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("-ml", ".%s {margin-left: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("mr", ".%s {margin-right: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!mr", ".%s {margin-right: %s !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("-mr", ".%s {margin-right: -%s;}", SINGLE_REPLACEMENT);

  add_util_class("space-x", ".%s {margin-left: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!space-x", ".%s {margin-left: %s !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("-space-x", ".%s {margin-left: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("space-y", ".%s {margin-top: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!space-y", ".%s {margin-top: %s !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("-space-y", ".%s {margin-top: -%s;}", SINGLE_REPLACEMENT);
}
