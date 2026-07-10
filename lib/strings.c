#include "strings.h"

char *concat(const char *s1, const char *s2) {
  size_t sz = strlen(s1) + strlen(s2) + 1;
  char *result = (char *)malloc(strlen(s1) + strlen(s2) + 1);
  if (result == NULL) {
    return "";
  }
  strcpy(result, s1);
  strcat(result, s2);
  result[sz - 1] = '\0';

  return result;
}

char **split_string(char *str, const char *delim, size_t *out_tokens_count) {
  char *token = strtok(str, delim);
  if (token == NULL) {
    return NULL;
  }
  char **tokens = (char **)malloc(sizeof(char *) * 2);
  size_t i = 0;
  while (token != NULL) {
    tokens[i] = strdup(token);
    i++;
    tokens = (char **)realloc(tokens, sizeof(char *) * (i + 1));
    token = strtok(NULL, delim);
  }

  *out_tokens_count = i;

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
