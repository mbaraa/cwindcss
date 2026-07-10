#include "regexes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

regex_t *compile_regex(const char *pattern) {
  regex_t *re = (regex_t *)malloc(sizeof(regex_t));
  int stat = regcomp(re, pattern, REG_EXTENDED);
  if (stat) {
    fprintf(stderr, "Could not compile regex\n");
    puts(pattern);
    exit(1);
  }
  return re;
}

MatchData *find_all_string_submatch(regex_t *re, const char *input) {
  int stat;
  char msgbuf[100];

  regmatch_t matches[3];
  char *cursor = (char *)input;

  MatchData *match_array = NULL;
  size_t match_count = 0;

  while (1) {
    stat = regexec(re, cursor, 3, matches, 0);
    if (stat == 0) {
      match_array = (MatchData *)realloc(match_array,
                                         (match_count + 1) * sizeof(MatchData));
      if (match_array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
      }

      int start = matches[0].rm_so;
      int end = matches[0].rm_eo;
      match_array[match_count].match = (char *)malloc(end - start + 1);
      strncpy(match_array[match_count].match, cursor + start, end - start);
      match_array[match_count].match[end - start] = '\0';

      start = matches[1].rm_so;
      end = matches[1].rm_eo;
      match_array[match_count].group1 = (char *)malloc(end - start + 1);
      strncpy(match_array[match_count].group1, cursor + start, end - start);
      match_array[match_count].group1[end - start] = '\0';

      if (matches[2].rm_so != 0 && matches[2].rm_eo != 0) {
        start = matches[2].rm_so;
        end = matches[2].rm_eo;
        match_array[match_count].group2 = (char *)malloc(end - start + 1);
        strncpy(match_array[match_count].group2, cursor + start, end - start);
        match_array[match_count].group2[end - start] = '\0';
      }

      match_count++;
      cursor += matches[0].rm_eo;
    } else if (stat == REG_NOMATCH) {
      break;
    } else {
      regerror(stat, re, msgbuf, sizeof(msgbuf));
      fprintf(stderr, "Regex match failed: %s\n", msgbuf);
      exit(1);
    }
  }

  match_array =
      (MatchData *)realloc(match_array, (match_count + 1) * sizeof(MatchData));
  if (match_array == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }
  match_array[match_count].match = NULL;
  match_array[match_count].group1 = NULL;
  match_array[match_count].group2 = NULL;

  return match_array;
}
