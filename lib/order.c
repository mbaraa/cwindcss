#include "order.h"
#include "utility_classes.h"

void init_order_classes() {
  add_util_class("order-none", ".%s {order: 0;}", NO_REPLACEMENT);
  add_util_class("!order-none", ".%s {order: 0 !important;}", NO_REPLACEMENT);
  add_util_class("order-1", ".%s {order: 1;}", NO_REPLACEMENT);
  add_util_class("!order-1", ".%s {order: 1 !important;}", NO_REPLACEMENT);
  add_util_class("order-2", ".%s {order: 2;}", NO_REPLACEMENT);
  add_util_class("!order-2", ".%s {order: 2 !important;}", NO_REPLACEMENT);
  add_util_class("order-3", ".%s {order: 3;}", NO_REPLACEMENT);
  add_util_class("!order-3", ".%s {order: 3 !important;}", NO_REPLACEMENT);
  add_util_class("order-4", ".%s {order: 4;}", NO_REPLACEMENT);
  add_util_class("!order-4", ".%s {order: 4 !important;}", NO_REPLACEMENT);
  add_util_class("order-5", ".%s {order: 5;}", NO_REPLACEMENT);
  add_util_class("!order-5", ".%s {order: 5 !important;}", NO_REPLACEMENT);
  add_util_class("order-6", ".%s {order: 6;}", NO_REPLACEMENT);
  add_util_class("!order-6", ".%s {order: 6 !important;}", NO_REPLACEMENT);
  add_util_class("order-7", ".%s {order: 7;}", NO_REPLACEMENT);
  add_util_class("!order-7", ".%s {order: 7 !important;}", NO_REPLACEMENT);
  add_util_class("order-8", ".%s {order: 8;}", NO_REPLACEMENT);
  add_util_class("!order-8", ".%s {order: 8 !important;}", NO_REPLACEMENT);
  add_util_class("order-9", ".%s {order: 9;}", NO_REPLACEMENT);
  add_util_class("!order-9", ".%s {order: 9 !important;}", NO_REPLACEMENT);
  add_util_class("order-10", ".%s {order: 10;}", NO_REPLACEMENT);
  add_util_class("!order-10", ".%s {order: 10 !important;}", NO_REPLACEMENT);
  add_util_class("order-11", ".%s {order: 11;}", NO_REPLACEMENT);
  add_util_class("!order-11", ".%s {order: 11 !important;}", NO_REPLACEMENT);
  add_util_class("order-12", ".%s {order: 12;}", NO_REPLACEMENT);
  add_util_class("!order-12", ".%s {order: 12 !important;}", NO_REPLACEMENT);
  add_util_class("order-first", ".%s {order: -9999;}", NO_REPLACEMENT);
  add_util_class("!order-first", ".%s {order: -9999 !important;}",
                 NO_REPLACEMENT);
  add_util_class("order-last", ".%s {order: 9999;}", NO_REPLACEMENT);
  add_util_class("!order-last", ".%s {order: 9999 !important;}",
                 NO_REPLACEMENT);

  add_util_class("justify-normal", ".%s {justify-content: normal;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-normal", ".%s {justify-content: normal !important;}",
                 NO_REPLACEMENT);
  add_util_class("justify-start", ".%s {justify-content: flex-start;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-start",
                 ".%s {justify-content: flex-start !important;}",
                 NO_REPLACEMENT);
  add_util_class("justify-end", ".%s {justify-content: flex-end;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-end", ".%s {justify-content: flex-end !important;}",
                 NO_REPLACEMENT);
  add_util_class("justify-center", ".%s {justify-content: center;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-center", ".%s {justify-content: center !important;}",
                 NO_REPLACEMENT);
  add_util_class("justify-between", ".%s {justify-content: space-between;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-between",
                 ".%s {justify-content: space-between !important;}",
                 NO_REPLACEMENT);
  add_util_class("justify-around", ".%s {justify-content: space-around;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-around",
                 ".%s {justify-content: space-around !important;}",
                 NO_REPLACEMENT);
  add_util_class("justify-evenly", ".%s {justify-content: space-evenly;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-evenly",
                 ".%s {justify-content: space-evenly !important;}",
                 NO_REPLACEMENT);
  add_util_class("justify-stretch", ".%s {justify-content: stretch;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-stretch",
                 ".%s {justify-content: stretch !important;}", NO_REPLACEMENT);

  add_util_class("justify-items-start", ".%s {justify-items: start;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-items-start",
                 ".%s {justify-items: start !important;}", NO_REPLACEMENT);
  add_util_class("justify-items-end", ".%s {justify-items: end;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-items-end", ".%s {justify-items: end !important;}",
                 NO_REPLACEMENT);
  add_util_class("justify-items-center", ".%s {justify-items: center;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-items-center",
                 ".%s {justify-items: center !important;}", NO_REPLACEMENT);
  add_util_class("justify-items-stretch", ".%s {justify-items: stretch;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-items-stretch",
                 ".%s {justify-items: stretch !important;}", NO_REPLACEMENT);

  add_util_class("justify-self-auto", ".%s {justify-self: auto;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-self-auto", ".%s {justify-self: auto !important;}",
                 NO_REPLACEMENT);
  add_util_class("justify-self-start", ".%s {justify-self: start;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-self-start", ".%s {justify-self: start !important;}",
                 NO_REPLACEMENT);
  add_util_class("justify-self-end", ".%s {justify-self: end;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-self-end", ".%s {justify-self: end !important;}",
                 NO_REPLACEMENT);
  add_util_class("justify-self-center", ".%s {justify-self: center;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-self-center",
                 ".%s {justify-self: center !important;}", NO_REPLACEMENT);
  add_util_class("justify-self-stretch", ".%s {justify-self: stretch;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-self-stretch",
                 ".%s {justify-self: stretch !important;}", NO_REPLACEMENT);

  add_util_class("self-auto", ".%s {align-self: auto;}", NO_REPLACEMENT);
  add_util_class("!self-auto", ".%s {align-self: auto !important;}",
                 NO_REPLACEMENT);
  add_util_class("self-start", ".%s {align-self: flex-start;}", NO_REPLACEMENT);
  add_util_class("!self-start", ".%s {align-self: flex-start !important;}",
                 NO_REPLACEMENT);
  add_util_class("self-end", ".%s {align-self: flex-end;}", NO_REPLACEMENT);
  add_util_class("!self-end", ".%s {align-self: flex-end !important;}",
                 NO_REPLACEMENT);
  add_util_class("self-center", ".%s {align-self: center;}", NO_REPLACEMENT);
  add_util_class("!self-center", ".%s {align-self: center !important;}",
                 NO_REPLACEMENT);
  add_util_class("self-stretch", ".%s {align-self: stretch;}", NO_REPLACEMENT);
  add_util_class("!self-stretch", ".%s {align-self: stretch !important;}",
                 NO_REPLACEMENT);
  add_util_class("self-baseline", ".%s {align-self: baseline;}",
                 NO_REPLACEMENT);
  add_util_class("!self-baseline", ".%s {align-self: baseline !important;}",
                 NO_REPLACEMENT);

  add_util_class("items-start", ".%s {align-items: flex-start;}",
                 NO_REPLACEMENT);
  add_util_class("!items-start", ".%s {align-items: flex-start !important;}",
                 NO_REPLACEMENT);
  add_util_class("items-end", ".%s {align-items: flex-end;}", NO_REPLACEMENT);
  add_util_class("!items-end", ".%s {align-items: flex-end !important;}",
                 NO_REPLACEMENT);
  add_util_class("items-center", ".%s {align-items: center;}", NO_REPLACEMENT);
  add_util_class("!items-center", ".%s {align-items: center !important;}",
                 NO_REPLACEMENT);
  add_util_class("items-baseline", ".%s {align-items: baseline;}",
                 NO_REPLACEMENT);
  add_util_class("!items-baseline", ".%s {align-items: baseline !important;}",
                 NO_REPLACEMENT);
  add_util_class("items-stretch", ".%s {align-items: stretch;}",
                 NO_REPLACEMENT);
  add_util_class("!items-stretch", ".%s {align-items: stretch !important;}",
                 NO_REPLACEMENT);
}
