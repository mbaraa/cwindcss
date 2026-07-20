#include "types.h"
#include <stdlib.h>

void pair_destroy(pair *p) {
  if (p->strstr != NULL) {
    if (p->strstr->first != NULL) {
      free(p->strstr->first);
    }
    if (p->strstr->second != NULL) {
      free(p->strstr->second);
    }
    free((void *)p->strstr);
  }
  free(p);
}
