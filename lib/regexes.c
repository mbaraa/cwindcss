#include "regexes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

regex_t *compile_regex(const char *pattern) {
  regex_t *re = (regex_t *)malloc(sizeof(regex_t));
  if (re == NULL) {
    fprintf(stderr, "Memory allocation failed for regex container\n");
    exit(1);
  }
  int stat = regcomp(re, pattern, REG_EXTENDED);
  if (stat) {
    fprintf(stderr, "Could not compile regex\n");
    puts(pattern);
    free(re);
    exit(1);
  }
  return re;
}

match_data *find_all_string_submatch(regex_t *re, const char *input,
                                     size_t *out_count) {
  int stat;
  char msgbuf[100];

  regmatch_t matches[3];
  char *cursor = (char *)input;

  match_data *match_array = NULL;
  size_t match_count = 0;

  while (1) {
    stat = regexec(re, cursor, 3, matches, 0);
    if (stat == 0) {
      match_data *temp = (match_data *)realloc(
          match_array, (match_count + 1) * sizeof(match_data));
      if (temp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        for (size_t k = 0; k < match_count; k++) {
          free(match_array[k].match);
          free(match_array[k].group1);
          free(match_array[k].group2);
        }
        free(match_array);
        exit(1);
      }
      match_array = temp;

      match_array[match_count].match = NULL;
      match_array[match_count].group1 = NULL;
      match_array[match_count].group2 = NULL;

      if (matches[0].rm_so != -1) {
        int start = matches[0].rm_so;
        int end = matches[0].rm_eo;
        match_array[match_count].match = (char *)malloc(end - start + 1);
        if (match_array[match_count].match) {
          strncpy(match_array[match_count].match, cursor + start, end - start);
          match_array[match_count].match[end - start] = '\0';
        }
      }

      if (matches[1].rm_so != -1) {
        int start = matches[1].rm_so;
        int end = matches[1].rm_eo;
        match_array[match_count].group1 = (char *)malloc(end - start + 1);
        if (match_array[match_count].group1) {
          strncpy(match_array[match_count].group1, cursor + start, end - start);
          match_array[match_count].group1[end - start] = '\0';
        }
      }

      if (matches[2].rm_so != -1) {
        int start = matches[2].rm_so;
        int end = matches[2].rm_eo;
        match_array[match_count].group2 = (char *)malloc(end - start + 1);
        if (match_array[match_count].group2) {
          strncpy(match_array[match_count].group2, cursor + start, end - start);
          match_array[match_count].group2[end - start] = '\0';
        }
      }

      match_count++;

      if (matches[0].rm_eo == 0) {
        cursor++;
      } else {
        cursor += matches[0].rm_eo;
      }

    } else if (stat == REG_NOMATCH) {
      break;
    } else {
      regerror(stat, re, msgbuf, sizeof(msgbuf));
      fprintf(stderr, "Regex match failed: %s\n", msgbuf);

      for (size_t k = 0; k < match_count; k++) {
        free(match_array[k].match);
        free(match_array[k].group1);
        free(match_array[k].group2);
      }
      free(match_array);
      exit(1);
    }
  }
  *out_count = match_count;

  return match_array;
}

void destroy_match_data(match_data m) {
  if (m.match != NULL) {
    free(m.match);
  }
  if (m.group1 != NULL) {
    free(m.group1);
  }
  if (m.group2 != NULL) {
    free(m.group2);
  }
}

void destroy_matches_data(match_data *matches, size_t count) {
  if (matches == NULL) {
    return;
  }

  for (size_t i = 0; i < count; i++) {
    free(matches[i].match);
    free(matches[i].group1);
    free(matches[i].group2);
  }

  free(matches);
}
