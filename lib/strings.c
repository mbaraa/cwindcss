#include "strings.h"
#include "stdio.h"

char *concat(const char *s1, const char *s2) {
  size_t sz = strlen(s1) + strlen(s2) + 1;
  char *result = (char *)malloc(sz);
  if (result == NULL) {
    return "";
  }
  strcpy(result, s1);
  strcat(result, s2);
  result[sz - 1] = '\0';

  return result;
}

array *split_string(char *str, const char *delim) {
  char *token = strtok(str, delim);
  if (token == NULL) {
    return NULL;
  }
  array *tokens = array_new(0, STRINGS);
  while (token != NULL) {
    int stat = array_push_string(tokens, strdup(token));
    if (stat != ARRAYS_OK) {
      printf("array error: %d\n", stat);
      return array_new(0, STRINGS);
    }
    token = strtok(NULL, delim);
  }

  ARRAY_ITER(tokens, token) { printf("#####token blyayt: %s\n", token.string); }

  return tokens;
}

bool has_suffix(const char *str, const char *suffix) {
  size_t str_len = strlen(str);
  size_t suffix_len = strlen(suffix);

  if (suffix_len > str_len) {
    return false;
  }

  return strcmp(str + str_len - suffix_len, suffix) == 0;
}
