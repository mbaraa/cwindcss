#include "./cwindcss.h"

typedef struct {
  char *match;
  char *group1;
  char *group2;
} MatchData;

struct str_bool_hash_item {
  char *key;
  bool value;
  UT_hash_handle hh;
};

// TODO: COMPARE THIS MADNESS TO LINEAR ARRAY SEARCH
struct class_fmt_hash_item {
  char *util_class;
  char *fmt_str;
  UT_hash_handle hh;
};

// start of utility classes hash map funcs
char *get_util_class(char *uc);
void add_util_class(char *uc, char *fmt);
// end of utility classes hash map funcs

// start of string utils funcs
char *concat(const char *s1, const char *s2);
char **split_string(char *str, const char *delim, size_t *out_tokens_count);
// end of string utils funcs

// start of regexp utils funcs
regex_t *compile_regex(const char *pattern);
MatchData *find_all_string_submatch(regex_t *re, const char *input);
// end of regexp utils funcs

regex_t *utility_class_pattern = NULL;
regex_t *numerical_utility_class_pattern = NULL;
regex_t *numerical_utility_class_value_pattern = NULL;
// global utility classes map
struct class_fmt_hash_item *classes_values = NULL;

////////////////////////////////////////////////////////////////
///////////////////  Init and Destroy funcs  ///////////////////
////////////////////////////////////////////////////////////////

void cwind_init() {
  // init regex patterns
  utility_class_pattern =
      compile_regex("^([-!]|!-|-\\!)?(.*:)?.*-(\\[.*\\]|\\w+)$");

  const char *responsive_modifiers = "xs:|sm:|md:|lg:|xl:|2xl:";
  const char *sizing_classes =
      "p|pt|pb|pl|pr|m|mt|mb|ml|mr|w|h|min-w|min-h|max-w|max-h|space-x|space-y";
  const char *size_units =
      "px|in|cm|mm|pt|pc|em|rem|%|ex|ch|vw|vh|dvh|dvw|vmin|vmax|deg|rad|grad|"
      "turn|s|ms|dpi|dcpi|dppx|Hz|kHz";

  char numerical_utility_class_pattern_buffer[256];
  snprintf(numerical_utility_class_pattern_buffer,
           sizeof(numerical_utility_class_pattern_buffer),
           "([-!]|!-|-\\!)?(%s)?(%s)-\\[\\d+(%s)\\]", responsive_modifiers,
           sizing_classes, size_units);
  numerical_utility_class_pattern =
      compile_regex(numerical_utility_class_pattern_buffer);

  char numerical_utility_class_value_pattern_buffer[128];
  snprintf(numerical_utility_class_value_pattern_buffer,
           sizeof(numerical_utility_class_value_pattern_buffer),
           "(%s)-\\[(.*)\\]", sizing_classes);
  numerical_utility_class_value_pattern =
      compile_regex(numerical_utility_class_value_pattern_buffer);

  // init util classes
  add_util_class("p", ".p%s {padding: %s;}");
  add_util_class("pt", ".pt%s {padding-top: %s;}");
  add_util_class("pb", ".pb%s {padding-bottom: %s;}");
  add_util_class("pl", ".pl%s {padding-left: %s;}");
  add_util_class("pr", ".pr%s {padding-right: %s;}");

  add_util_class("m", ".m%s {margin: %s;}");
  add_util_class("mt", ".mt%s {margin-top: %s;}");
  add_util_class("mb", ".mb%s {margin-bottom: %s;}");
  add_util_class("ml", ".ml%s {margin-left: %s;}");
  add_util_class("mr", ".mr%s {margin-right: %s;}");
}

void cwind_destroy() {
  regfree(utility_class_pattern);
  regfree(numerical_utility_class_pattern);
  regfree(numerical_utility_class_value_pattern);
}

////////////////////////////////////////////////////////////////
//////////////////////  The Actual Juice  //////////////////////
////////////////////////////////////////////////////////////////

char **cwind_extract_css_classes(char *html, size_t *out_classes_count) {
  const char *classes_pattern_str = "class=\"([^\"]+)\"";
  regex_t *classes_pattern = compile_regex(classes_pattern_str);

  MatchData *matches = find_all_string_submatch(classes_pattern, html);
  size_t sz = 0;
  while (matches[sz].match != NULL) {
    sz++;
  }
  if (sz == 0) {
    *out_classes_count = 0;
    return NULL;
  }

  char *all_classes = (char *)malloc(sizeof(char) * sz);
  if (sz > 0) {
    all_classes = strdup(matches[0].group1);
    free(matches[0].match);
    free(matches[0].group1);
  }
  for (size_t i = 1; i < sz; i++) {
    all_classes = concat(all_classes, " ");
    all_classes = concat(all_classes, strdup(matches[i].group1));
    free(matches[i].match);
    free(matches[i].group1);
  }

  size_t tokens_count = 0;
  char **tokens = split_string(all_classes, " ", &tokens_count);
  if (tokens_count == 0) {
    *out_classes_count = 0;
    return NULL;
  }
  struct str_bool_hash_item *unique_classes = NULL;
  for (size_t i = 0; i < tokens_count; i++) {
    struct str_bool_hash_item *item = NULL;

    HASH_FIND_STR(unique_classes, tokens[i], item);
    if (item == NULL) {
      item = (struct str_bool_hash_item *)malloc(
          sizeof(struct str_bool_hash_item));
      item->key = tokens[i];
      item->value = true;
      HASH_ADD_STR(unique_classes, key, item);
    }
  }

  size_t num_classes = unique_classes == NULL ? 0 : HASH_COUNT(unique_classes);
  *out_classes_count = num_classes;
  char **classes = (char **)malloc(sizeof(char *) * num_classes);

  struct str_bool_hash_item *item = NULL, *tmp = NULL;
  int i = 0;
  HASH_ITER(hh, unique_classes, item, tmp) {
    classes[i++] = strdup(item->key);
    HASH_DEL(unique_classes, item);
    free(item);
  }

  regfree(classes_pattern);

  return classes;
}

// replace char* with buffer
char *cwind_process_utility_classes(char *input_html) {
  printf("%s\n", input_html);
  int stat;
  char msgbuf[100];

  size_t classes_count = 0;
  char **classes = cwind_extract_css_classes(input_html, &classes_count);
  char *output = "";
  for (size_t i = 0; i < classes_count; i++) {
    stat = regexec(utility_class_pattern, classes[i], 0, NULL, 0);
    if (stat) {
      continue;
    }
    /* stat = regexec(numerical_utility_class_pattern, classes[i], 0, NULL, 0);
     */
    /* if (stat) { */
    /* printf("%s doesn't match\n", classes[i]); */
    /* continue; */
    /* } */

    MatchData *value = find_all_string_submatch(
        numerical_utility_class_value_pattern, classes[i]);
    /* size_t j = 0; */
    /* while (value[j].match != NULL) { */
    if (value[0].match != NULL) {
      char *css_class_format = get_util_class(value[0].group1);
      size_t len = strlen(css_class_format);

      char *css_class_definition =
          (char *)malloc(len + (2 * strlen(value[0].group2)));
      sprintf(css_class_definition, css_class_format, value[0].group2,
              value[0].group2);
      output = concat(output, css_class_definition);
      output = concat(output, " ");

      /* printf(get_util_class(value[0].group1), value[0].group2,
       * value[0].group2); */
      /* puts(""); */
    }
    /* j++; */
    /* } */
  }
  output[strlen(output) - 1] = '\0';
  /* printf("OUT CLASSES: %s\n", output); */

  return output;
}

////////////////////////////////////////////////////////////////
////////////////////  Global HashMap Utils  ////////////////////
////////////////////////////////////////////////////////////////

void add_util_class(char *uc, char *fmt) {
  struct class_fmt_hash_item *s =
      (struct class_fmt_hash_item *)malloc(sizeof(struct class_fmt_hash_item));
  s->util_class = uc;
  s->fmt_str = fmt;
  HASH_ADD_STR(classes_values, util_class, s);
}

char *get_util_class(char *uc) {
  struct class_fmt_hash_item *s;

  HASH_FIND_STR(classes_values, uc, s);
  if (s == NULL) {
    return NULL;
  }

  return s->fmt_str;
}

////////////////////////////////////////////////////////////////
////////////////////////  String Utils  ////////////////////////
////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////
////////////////////////  RexExp Utils  ////////////////////////
////////////////////////////////////////////////////////////////

regex_t *compile_regex(const char *pattern) {
  regex_t *re = (regex_t *)malloc(sizeof(regex_t));
  int stat = regcomp(re, pattern, REG_EXTENDED);
  if (stat) {
    fprintf(stderr, "Could not compile regex\n");
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
