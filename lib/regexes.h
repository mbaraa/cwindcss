#ifndef _REGEXES_H
#define _REGEXES_H

#include <regex.h>

typedef struct {
  char *match;
  char *group1;
  char *group2;
} MatchData;

regex_t *compile_regex(const char *pattern);
MatchData *find_all_string_submatch(regex_t *re, const char *input);

#endif // !_REGEXES_H
