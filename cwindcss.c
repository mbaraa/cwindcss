#include "./cwindcss.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

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

enum utility_class_type {
  SPACING,             // [class_name, size]
  SIZING,              // [class_name, size]
  POSITIONING_PLACING, // [class_name]
  POSITIONING,         // [class_name, size]
  INSET,               // [class_name, size, size]
};

// TODO: COMPARE THIS MADNESS TO LINEAR ARRAY SEARCH
struct class_fmt_hash_item {
  char *util_class;
  char *fmt_str;
  enum utility_class_type type;
  UT_hash_handle hh;
};

// start of utility classes funcs
struct class_fmt_hash_item *get_util_class(char *uc);
void add_util_class(char *uc, char *fmt, enum utility_class_type type);
// end of utility classes funcs

// start of string utils funcs
char *concat(const char *s1, const char *s2);
char **split_string(char *str, const char *delim, size_t *out_tokens_count);
// end of string utils funcs

// start of regexp utils funcs
regex_t *compile_regex(const char *pattern);
MatchData *find_all_string_submatch(regex_t *re, const char *input);
// end of regexp utils funcs

regex_t *utility_class_pattern = NULL;
regex_t *numerical_utility_class_value_pattern = NULL;
regex_t *single_letter_utility_class_value_pattern = NULL;
// global utility classes map
struct class_fmt_hash_item *classes_values = NULL;

////////////////////////////////////////////////////////////////
///////////////////  Init and Destroy funcs  ///////////////////
////////////////////////////////////////////////////////////////

void cwind_init() {
  // init regex patterns
  utility_class_pattern =
      compile_regex("^([-!]|!-|-\\!)?(.*:)?.*-?(\\[.*\\]|\\w+)$");

  const char *responsive_modifiers = "xs:|sm:|md:|lg:|xl:|2xl:";
  size_t responsive_modifiers_len = strlen(responsive_modifiers);
  const char *sizing_classes =
      "p|pt|pb|pl|pr|m|mt|mb|ml|mr|w|h|min-w|min-h|max-w|max-h|space-x|space-y|"
      "top|bottom|left|right|z|inset";
  size_t sizing_classes_len = strlen(sizing_classes);
  const char *size_units =
      "px|in|cm|mm|pt|pc|em|rem|%|ex|ch|vw|vh|dvh|dvw|vmin|vmax|deg|rad|grad|"
      "turn|s|ms|dpi|dcpi|dppx|Hz|kHz";
  size_t size_units_len = strlen(size_units);

  char numerical_utility_class_value_pattern_buffer[16 + sizing_classes_len];
  snprintf(numerical_utility_class_value_pattern_buffer,
           sizeof(numerical_utility_class_value_pattern_buffer),
           "(%s)-\\[(.*)\\]", sizing_classes);
  numerical_utility_class_value_pattern =
      compile_regex(numerical_utility_class_value_pattern_buffer);

  single_letter_utility_class_value_pattern = compile_regex("([a-z]+)");

  // init util classes
  // spacing
  add_util_class("p", ".%s {padding: %s;}", SPACING);
  add_util_class("pt", ".%s {padding-top: %s;}", SPACING);
  add_util_class("pb", ".%s {padding-bottom: %s;}", SPACING);
  add_util_class("pl", ".%s {padding-left: %s;}", SPACING);
  add_util_class("pr", ".%s {padding-right: %s;}", SPACING);

  add_util_class("m", ".%s {margin: %s;}", SPACING);
  add_util_class("mt", ".%s {margin-top: %s;}", SPACING);
  add_util_class("mb", ".%s {margin-bottom: %s;}", SPACING);
  add_util_class("ml", ".%s {margin-left: %s;}", SPACING);
  add_util_class("mr", ".%s {margin-right: %s;}", SPACING);

  add_util_class("space-x", ".%s {margin-left: %s;}", SPACING);
  add_util_class("space-y", ".%s {margin-top: %s;}", SPACING);

  // sizing
  add_util_class("w", ".%s {width: %s;}", SIZING);
  add_util_class("h", ".%s {height: %s;}", SIZING);
  add_util_class("max-w", ".%s {max-width: %s;}", SIZING);
  add_util_class("max-h", ".%s {max-height: %s;}", SIZING);
  add_util_class("min-w", ".%s {min-width: %s;}", SIZING);
  add_util_class("min-h", ".%s {min-height: %s;}", SIZING);

  // positioning placing
  add_util_class("static", ".%s {position: static;}", POSITIONING_PLACING);
  add_util_class("fixed", ".%s {position: fixed;}", POSITIONING_PLACING);
  add_util_class("absolute", ".%s {position: absolute;}", POSITIONING_PLACING);
  add_util_class("relative", ".%s {position: relative;}", POSITIONING_PLACING);
  add_util_class("sticky", ".%s {position: sticky;}", POSITIONING_PLACING);

  // positioning
  add_util_class("top", ".%s {top: %s;}", POSITIONING);
  add_util_class("right", ".%s {right: %s;}", POSITIONING);
  add_util_class("bottom", ".%s {bottom: %s;}", POSITIONING);
  add_util_class("left", ".%s {left: %s;}", POSITIONING);
  add_util_class("z", ".%s {z-index: %s;}", POSITIONING);
  add_util_class("inset", ".%s {inset: %s;}", POSITIONING);

  // inset
  add_util_class("inset-x", ".%s {left: %s; right: %s;}", INSET);
  add_util_class("inset-y", ".%s {top: %s; bottom: %s;}", INSET);
}

void cwind_destroy() {
  regfree(utility_class_pattern);
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

    MatchData *value = find_all_string_submatch(
        numerical_utility_class_value_pattern, classes[i]);
    /* size_t j = 0; */
    /* while (value[j].match != NULL) { */
    if (value[0].match != NULL) {
      struct class_fmt_hash_item *css_class_format =
          get_util_class(value[0].group1);
      if (css_class_format == NULL || css_class_format->fmt_str == NULL) {
        continue;
      }
      size_t len = strlen(css_class_format->fmt_str);

      char *css_class_definition =
          (char *)malloc(len + (2 * strlen(value[0].group2)));
      size_t css_class_name_len = strlen(value[0].match);
      char *css_class_name = (char *)malloc(css_class_name_len + 2);
      for (size_t i = 0, j = 0; i < css_class_name_len; i++, j++) {
        char chr = value[0].match[i];
        if (!((chr >= 'a' && chr <= 'z') || (chr >= 'A' && chr <= 'Z') ||
              (chr >= '0' && chr <= '9') || chr == '-' || chr == '_')) {
          css_class_name[j] = '\\';
          css_class_name[++j] = chr;
          continue;
        }
        css_class_name[j] = chr;
      }

      switch (css_class_format->type) {
      case SPACING:
        sprintf(css_class_definition, css_class_format->fmt_str, css_class_name,
                value[0].group2);
        break;
      case SIZING:
        sprintf(css_class_definition, css_class_format->fmt_str, css_class_name,
                value[0].group2);
        break;
      case POSITIONING_PLACING:
        /* sprintf(css_class_definition, css_class_format->fmt_str,
         * css_class_name); */
        break;
      case POSITIONING:
        sprintf(css_class_definition, css_class_format->fmt_str, css_class_name,
                value[0].group2);
        break;
      case INSET:
        sprintf(css_class_definition, css_class_format->fmt_str, css_class_name,
                value[0].group2, value[0].group2);
        break;
      }

      output = concat(output, strdup(css_class_definition));
      output = concat(output, " ");
      free(css_class_definition);
      continue;
    }
    value = find_all_string_submatch(single_letter_utility_class_value_pattern,
                                     classes[i]);
    /* size_t j = 0; */
    /* while (value[j].match != NULL) { */
    if (value[0].match != NULL && strcmp(value[0].match, classes[i]) == 0) {
      struct class_fmt_hash_item *css_class_format =
          get_util_class(value[0].match);
      if (css_class_format == NULL || css_class_format->fmt_str == NULL) {
        continue;
      }

      size_t len = strlen(css_class_format->fmt_str);

      char *css_class_definition =
          (char *)malloc(len + (2 * strlen(value[0].match)));
      size_t css_class_name_len = strlen(value[0].match);
      sprintf(css_class_definition, css_class_format->fmt_str, value[0].match);

      output = concat(output, strdup(css_class_definition));
      output = concat(output, " ");
      free(css_class_definition);
      continue;
    }
    /* j++; */
    /* } */
  }
  output[strlen(output) - 1] = '\0';

  return output;
}

////////////////////////////////////////////////////////////////
////////////////////  Global HashMap Utils  ////////////////////
////////////////////////////////////////////////////////////////

void add_util_class(char *uc, char *fmt, enum utility_class_type type) {
  struct class_fmt_hash_item *s =
      (struct class_fmt_hash_item *)malloc(sizeof(struct class_fmt_hash_item));
  s->util_class = uc;
  s->fmt_str = fmt;
  s->type = type;
  HASH_ADD_STR(classes_values, util_class, s);
}

struct class_fmt_hash_item *get_util_class(char *uc) {
  struct class_fmt_hash_item *util_class = NULL;

  HASH_FIND_STR(classes_values, uc, util_class);
  if (util_class == NULL) {
    return NULL;
  }

  return util_class;
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
