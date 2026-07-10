#ifndef _STRINGS_H
#define _STRINGS_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char *concat(const char *s1, const char *s2);
char **split_string(char *str, const char *delim, size_t *out_tokens_count);
bool has_suffix(const char *str, const char *suffix);

#endif // _STRINGS_H
