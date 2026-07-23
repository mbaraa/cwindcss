#include "types.h"
#include <stdlib.h>

pair *pair_new() {
  pair *p = (pair *)malloc(sizeof(pair));
  p->intint = NULL;
  p->strstr = (strstr_pair *)malloc(sizeof(strstr_pair));
  if (!p->strstr) {
    free(p);
    return NULL;
  }

  p->strstr->first = NULL;
  p->strstr->second = NULL;

  //  p->intint = (intint_pair *)malloc(sizeof(intint_pair));
  //  if (!p->intint) {
  //    free(p);
  //    return NULL;
  //  }

  return p;
}

void pair_destroy(pair *p) {
  if (p->strstr != NULL) {
    if (p->strstr->first != NULL) {
      free((void *)p->strstr->first);
    }
    if (p->strstr->second != NULL) {
      free(p->strstr->second);
    }
    free((void *)p->strstr);
  }
  /* if (p->intint != NULL) { */
  /* free((void *)p->intint); */
  /* } */
  free(p);
}
