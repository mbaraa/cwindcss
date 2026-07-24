#ifndef _REGEXES_H
#define _REGEXES_H

#include <regex.h>

typedef struct {
  char *match;
  char *group1;
  char *group2;
} match_data;

regex_t *compile_regex(const char *pattern);
match_data *find_all_string_submatch(regex_t *re, const char *input,
                                     size_t *out_count);
void destroy_match_data(match_data m);
void destroy_matches_data(match_data *matches, size_t count);

#endif // !_REGEXES_H
