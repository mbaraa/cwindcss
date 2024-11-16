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

enum class_value_type {
  NO_REPLACEMENT,     // [class_name]
  SINGLE_REPLACEMENT, // [class_name, size]
  DOUBLE_REPLACEMENT, // [class_name, size, size]
};

// TODO: COMPARE THIS MADNESS TO LINEAR ARRAY SEARCH
struct class_fmt_hash_item {
  char *util_class;
  char *fmt_str;
  enum class_value_type type;
  UT_hash_handle hh;
};

// start of utility classes funcs
struct class_fmt_hash_item *get_util_class(char *uc);
void add_util_class(char *uc, char *fmt, enum class_value_type type);
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
regex_t *only_words_utility_class_value_pattern = NULL;
// global utility classes map
struct class_fmt_hash_item *classes_values = NULL;

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
      case SINGLE_REPLACEMENT:
        sprintf(css_class_definition, css_class_format->fmt_str, css_class_name,
                value[0].group2);
        break;
      case NO_REPLACEMENT:
        /* sprintf(css_class_definition, css_class_format->fmt_str,
         * css_class_name); */
        break;
      case DOUBLE_REPLACEMENT:
        sprintf(css_class_definition, css_class_format->fmt_str, css_class_name,
                value[0].group2, value[0].group2);
        break;
      }

      output = concat(output, strdup(css_class_definition));
      output = concat(output, " ");
      free(css_class_definition);
      continue;
    }
    value = find_all_string_submatch(only_words_utility_class_value_pattern,
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

void add_util_class(char *uc, char *fmt, enum class_value_type type) {
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

////////////////////////////////////////////////////////////////
///////////////////  Init and Destroy funcs  ///////////////////
////////////////////////////////////////////////////////////////

void cwind_init() {
  // init regex patterns
  utility_class_pattern = compile_regex(
      "^-?!?([a-zA-Z0-9]+:)?[_a-zA-Z]+[_a-zA-Z0-9-]*(-(\\[.*\\]|\\w+))?$");

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
           "(-?!?%s)-\\[(.*)\\]", sizing_classes);
  numerical_utility_class_value_pattern =
      compile_regex(numerical_utility_class_value_pattern_buffer);

  only_words_utility_class_value_pattern = compile_regex("^([\\-\\!a-z0-9]+)$");

  // init util classes
  // spacing
  add_util_class("p", ".%s {padding: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!p", ".%s {padding: %s !important;}", SINGLE_REPLACEMENT);
  add_util_class("-p", ".%s {padding: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("pt", ".%s {padding-top: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!pt", ".%s {padding-top: %s !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("-pt", ".%s {padding-top: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("pb", ".%s {padding-bottom: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!pb", ".%s {padding-bottom: %s !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("-pb", ".%s {padding-bottom: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("pl", ".%s {padding-left: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!pl", ".%s {padding-left: %s !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("-pl", ".%s {padding-left: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("pr", ".%s {padding-right: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!pr", ".%s {padding-right: %s !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("-pr", ".%s {padding-right: -%s;}", SINGLE_REPLACEMENT);

  add_util_class("m", ".%s {margin: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!m", ".%s {margin: %s !important;}", SINGLE_REPLACEMENT);
  add_util_class("-m", ".%s {margin: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("mt", ".%s {margin-top: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!mt", ".%s {margin-top: %s !important;}", SINGLE_REPLACEMENT);
  add_util_class("-mt", ".%s {margin-top: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("mb", ".%s {margin-bottom: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!mb", ".%s {margin-bottom: %s !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("-mb", ".%s {margin-bottom: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("ml", ".%s {margin-left: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!ml", ".%s {margin-left: %s !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("-ml", ".%s {margin-left: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("mr", ".%s {margin-right: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!mr", ".%s {margin-right: %s !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("-mr", ".%s {margin-right: -%s;}", SINGLE_REPLACEMENT);

  add_util_class("space-x", ".%s {margin-left: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!space-x", ".%s {margin-left: %s !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("-space-x", ".%s {margin-left: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("space-y", ".%s {margin-top: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!space-y", ".%s {margin-top: %s !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("-space-y", ".%s {margin-top: -%s;}", SINGLE_REPLACEMENT);

  // sizing
  add_util_class("w", ".%s {width: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!w", ".%s {width: %s !important;}", SINGLE_REPLACEMENT);
  add_util_class("-w", ".%s {width: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("h", ".%s {height: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!h", ".%s {height: %s !important;}", SINGLE_REPLACEMENT);
  add_util_class("-h", ".%s {height: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("max-w", ".%s {max-width: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!max-w", ".%s {max-width: %s !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("-max-w", ".%s {max-width: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("max-h", ".%s {max-height: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!max-h", ".%s {max-height: %s !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("-max-h", ".%s {max-height: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("min-w", ".%s {min-width: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!min-w", ".%s {min-width: %s !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("-min-w", ".%s {min-width: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("min-h", ".%s {min-height: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!min-h", ".%s {min-height: %s !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("-min-h", ".%s {min-height: -%s;}", SINGLE_REPLACEMENT);

  // positioning placing
  add_util_class("static", ".%s {position: static;}", NO_REPLACEMENT);
  add_util_class("!static", ".%s {position: static !important;}",
                 NO_REPLACEMENT);
  add_util_class("fixed", ".%s {position: fixed;}", NO_REPLACEMENT);
  add_util_class("!fixed", ".%s {position: fixed !important;}", NO_REPLACEMENT);
  add_util_class("absolute", ".%s {position: absolute;}", NO_REPLACEMENT);
  add_util_class("!absolute", ".%s {position: absolute !important;}",
                 NO_REPLACEMENT);
  add_util_class("relative", ".%s {position: relative;}", NO_REPLACEMENT);
  add_util_class("!relative", ".%s {position: relative !important;}",
                 NO_REPLACEMENT);
  add_util_class("sticky", ".%s {position: sticky;}", NO_REPLACEMENT);
  add_util_class("!sticky", ".%s {position: sticky !important;}",
                 NO_REPLACEMENT);

  // inset
  add_util_class("inset-x", ".%s {left: %s; right: %s;}", DOUBLE_REPLACEMENT);
  add_util_class("!inset-x", ".%s {left: %s !important; right: %s !important;}",
                 DOUBLE_REPLACEMENT);
  add_util_class("-inset-x", ".%s {left: -%s; right: -%s;}",
                 DOUBLE_REPLACEMENT);
  add_util_class("inset-y", ".%s {top: %s; bottom: %s;}", DOUBLE_REPLACEMENT);
  add_util_class("!inset-y", ".%s {top: %s !important; bottom: %s !important;}",
                 DOUBLE_REPLACEMENT);
  add_util_class("-inset-y", ".%s {top: -%s; bottom: -%s;}",
                 DOUBLE_REPLACEMENT);

  // positioning
  add_util_class("top", ".%s {top: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!top", ".%s {top: %s !important;}", SINGLE_REPLACEMENT);
  add_util_class("-top", ".%s {top: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("right", ".%s {right: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!right", ".%s {right: %s !important;}", SINGLE_REPLACEMENT);
  add_util_class("-right", ".%s {right: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("bottom", ".%s {bottom: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!bottom", ".%s {bottom: %s !important;}", SINGLE_REPLACEMENT);
  add_util_class("-bottom", ".%s {bottom: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("left", ".%s {left: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!left", ".%s {left: %s !important;}", SINGLE_REPLACEMENT);
  add_util_class("-left", ".%s {left: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("z", ".%s {z-index: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!z", ".%s {z-index: %s !important;}", SINGLE_REPLACEMENT);
  add_util_class("-z", ".%s {z-index: -%s;}", SINGLE_REPLACEMENT);
  add_util_class("inset", ".%s {inset: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!inset", ".%s {inset: %s !important;}", SINGLE_REPLACEMENT);
  add_util_class("-inset", ".%s {inset: -%s;}", SINGLE_REPLACEMENT);

  // display
  add_util_class("block", ".%s {display: block;}", NO_REPLACEMENT);
  add_util_class("!block", ".%s {display: block !important;}", NO_REPLACEMENT);
  add_util_class("inline-block", ".%s {display: inline-block;}",
                 NO_REPLACEMENT);
  add_util_class("!inline-block", ".%s {display: inline-block !important;}",
                 NO_REPLACEMENT);
  add_util_class("inline", ".%s {display: inline;}", NO_REPLACEMENT);
  add_util_class("!inline", ".%s {display: inline !important;}",
                 NO_REPLACEMENT);
  add_util_class("flex", ".%s {display: flex;}", NO_REPLACEMENT);
  add_util_class("!flex", ".%s {display: flex !important;}", NO_REPLACEMENT);
  add_util_class("grid", ".%s {display: grid;}", NO_REPLACEMENT);
  add_util_class("!grid", ".%s {display: grid !important;}", NO_REPLACEMENT);
  add_util_class("table", ".%s {display: table;}", NO_REPLACEMENT);
  add_util_class("!table", ".%s {display: table !important;}", NO_REPLACEMENT);
  add_util_class("hidden", ".%s {display: none;}", NO_REPLACEMENT);
  add_util_class("!hidden", ".%s {display: none !important;}", NO_REPLACEMENT);

  // flexbox
  add_util_class("flex-row", ".%s {flex-direction: row;}", NO_REPLACEMENT);
  add_util_class("!flex-row", ".%s {flex-direction: row !important;}",
                 NO_REPLACEMENT);
  add_util_class("flex-row-reverse", ".%s {flex-direction: row-reverse;}",
                 NO_REPLACEMENT);
  add_util_class("!flex-row-reverse",
                 ".%s {flex-direction: row-reverse !important;}",
                 NO_REPLACEMENT);
  add_util_class("flex-col", ".%s {flex-direction: col;}", NO_REPLACEMENT);
  add_util_class("!flex-col", ".%s {flex-direction: col !important;}",
                 NO_REPLACEMENT);
  add_util_class("flex-col-reverse", ".%s {flex-direction: column-reverse;}",
                 NO_REPLACEMENT);
  add_util_class("!flex-col-reverse",
                 ".%s {flex-direction: column-reverse !important;}",
                 NO_REPLACEMENT);
  add_util_class("flex-wrap", ".%s {flex-wrap: wrap;}", NO_REPLACEMENT);
  add_util_class("!flex-wrap", ".%s {flex-wrap: wrap !important;}",
                 NO_REPLACEMENT);
  add_util_class("flex-wrap-reverse", ".%s {flex-wrap: wrap-reverse;}",
                 NO_REPLACEMENT);
  add_util_class("!flex-wrap-reverse",
                 ".%s {flex-wrap: wrap-reverse !important;}", NO_REPLACEMENT);
  add_util_class("flex-nowrap", ".%s {flex-wrap: nowrap;}", NO_REPLACEMENT);
  add_util_class("!flex-nowrap", ".%s {flex-wrap: nowrap !important;}",
                 NO_REPLACEMENT);
  add_util_class("grow", ".%s {flex-grow: 1;}", NO_REPLACEMENT);
  add_util_class("!grow", ".%s {flex-grow: 1 !important;}", NO_REPLACEMENT);
  add_util_class("grow-0", ".%s {flex-grow: 1;}", NO_REPLACEMENT);
  add_util_class("!grow-0", ".%s {flex-grow: 1 !important;}", NO_REPLACEMENT);
  add_util_class("shrink", ".%s {flex-shrink: 1;}", NO_REPLACEMENT);
  add_util_class("!shrink", ".%s {flex-shrink: 1 !important;}", NO_REPLACEMENT);
  add_util_class("shrink-0", ".%s {flex-shrink: 0;}", NO_REPLACEMENT);
  add_util_class("!shrink-0", ".%s {flex-shrink: 0 !important;}",
                 NO_REPLACEMENT);

  // order
  add_util_class("order-none", ".%s {order: 0;}", NO_REPLACEMENT);
  add_util_class("!order-none", ".%s {order: 0 !important;}", NO_REPLACEMENT);
  add_util_class("order-1", ".%s {order: 1;}", NO_REPLACEMENT);
  add_util_class("!order-1", ".%s {order: 1 !important;}", NO_REPLACEMENT);
  add_util_class("order-2", ".%s {order: 2;}", NO_REPLACEMENT);
  add_util_class("!order-2", ".%s {order: 2 !important;}", NO_REPLACEMENT);
  add_util_class("order-3", ".%s {order: 3;}", NO_REPLACEMENT);
  add_util_class("!order-3", ".%s {order: 3 !important;}", NO_REPLACEMENT);
  add_util_class("order-4", ".%s {order: 4;}", NO_REPLACEMENT);
  add_util_class("!order-4", ".%s {order: 4 !important;}", NO_REPLACEMENT);
  add_util_class("order-5", ".%s {order: 5;}", NO_REPLACEMENT);
  add_util_class("!order-5", ".%s {order: 5 !important;}", NO_REPLACEMENT);
  add_util_class("order-6", ".%s {order: 6;}", NO_REPLACEMENT);
  add_util_class("!order-6", ".%s {order: 6 !important;}", NO_REPLACEMENT);
  add_util_class("order-7", ".%s {order: 7;}", NO_REPLACEMENT);
  add_util_class("!order-7", ".%s {order: 7 !important;}", NO_REPLACEMENT);
  add_util_class("order-8", ".%s {order: 8;}", NO_REPLACEMENT);
  add_util_class("!order-8", ".%s {order: 8 !important;}", NO_REPLACEMENT);
  add_util_class("order-9", ".%s {order: 9;}", NO_REPLACEMENT);
  add_util_class("!order-9", ".%s {order: 9 !important;}", NO_REPLACEMENT);
  add_util_class("order-10", ".%s {order: 10;}", NO_REPLACEMENT);
  add_util_class("!order-10", ".%s {order: 10 !important;}", NO_REPLACEMENT);
  add_util_class("order-11", ".%s {order: 11;}", NO_REPLACEMENT);
  add_util_class("!order-11", ".%s {order: 11 !important;}", NO_REPLACEMENT);
  add_util_class("order-12", ".%s {order: 12;}", NO_REPLACEMENT);
  add_util_class("!order-12", ".%s {order: 12 !important;}", NO_REPLACEMENT);
  add_util_class("order-first", ".%s {order: -9999;}", NO_REPLACEMENT);
  add_util_class("!order-first", ".%s {order: -9999 !important;}",
                 NO_REPLACEMENT);
  add_util_class("order-last", ".%s {order: 9999;}", NO_REPLACEMENT);
  add_util_class("!order-last", ".%s {order: 9999 !important;}",
                 NO_REPLACEMENT);

  add_util_class("justify-normal", ".%s {justify-content: normal;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-normal", ".%s {justify-content: normal !important;}",
                 NO_REPLACEMENT);
  add_util_class("justify-start", ".%s {justify-content: flex-start;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-start",
                 ".%s {justify-content: flex-start !important;}",
                 NO_REPLACEMENT);
  add_util_class("justify-end", ".%s {justify-content: flex-end;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-end", ".%s {justify-content: flex-end !important;}",
                 NO_REPLACEMENT);
  add_util_class("justify-center", ".%s {justify-content: center;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-center", ".%s {justify-content: center !important;}",
                 NO_REPLACEMENT);
  add_util_class("justify-between", ".%s {justify-content: space-between;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-between",
                 ".%s {justify-content: space-between !important;}",
                 NO_REPLACEMENT);
  add_util_class("justify-around", ".%s {justify-content: space-around;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-around",
                 ".%s {justify-content: space-around !important;}",
                 NO_REPLACEMENT);
  add_util_class("justify-evenly", ".%s {justify-content: space-evenly;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-evenly",
                 ".%s {justify-content: space-evenly !important;}",
                 NO_REPLACEMENT);
  add_util_class("justify-stretch", ".%s {justify-content: stretch;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-stretch",
                 ".%s {justify-content: stretch !important;}", NO_REPLACEMENT);

  add_util_class("justify-items-start", ".%s {justify-items: start;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-items-start",
                 ".%s {justify-items: start !important;}", NO_REPLACEMENT);
  add_util_class("justify-items-end", ".%s {justify-items: end;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-items-end", ".%s {justify-items: end !important;}",
                 NO_REPLACEMENT);
  add_util_class("justify-items-center", ".%s {justify-items: center;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-items-center",
                 ".%s {justify-items: center !important;}", NO_REPLACEMENT);
  add_util_class("justify-items-stretch", ".%s {justify-items: stretch;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-items-stretch",
                 ".%s {justify-items: stretch !important;}", NO_REPLACEMENT);

  add_util_class("justify-self-auto", ".%s {justify-self: auto;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-self-auto", ".%s {justify-self: auto !important;}",
                 NO_REPLACEMENT);
  add_util_class("justify-self-start", ".%s {justify-self: start;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-self-start", ".%s {justify-self: start !important;}",
                 NO_REPLACEMENT);
  add_util_class("justify-self-end", ".%s {justify-self: end;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-self-end", ".%s {justify-self: end !important;}",
                 NO_REPLACEMENT);
  add_util_class("justify-self-center", ".%s {justify-self: center;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-self-center",
                 ".%s {justify-self: center !important;}", NO_REPLACEMENT);
  add_util_class("justify-self-stretch", ".%s {justify-self: stretch;}",
                 NO_REPLACEMENT);
  add_util_class("!justify-self-stretch",
                 ".%s {justify-self: stretch !important;}", NO_REPLACEMENT);

  add_util_class("self-auto", ".%s {align-self: auto;}", NO_REPLACEMENT);
  add_util_class("!self-auto", ".%s {align-self: auto !important;}",
                 NO_REPLACEMENT);
  add_util_class("self-start", ".%s {align-self: flex-start;}", NO_REPLACEMENT);
  add_util_class("!self-start", ".%s {align-self: flex-start !important;}",
                 NO_REPLACEMENT);
  add_util_class("self-end", ".%s {align-self: flex-end;}", NO_REPLACEMENT);
  add_util_class("!self-end", ".%s {align-self: flex-end !important;}",
                 NO_REPLACEMENT);
  add_util_class("self-center", ".%s {align-self: center;}", NO_REPLACEMENT);
  add_util_class("!self-center", ".%s {align-self: center !important;}",
                 NO_REPLACEMENT);
  add_util_class("self-stretch", ".%s {align-self: stretch;}", NO_REPLACEMENT);
  add_util_class("!self-stretch", ".%s {align-self: stretch !important;}",
                 NO_REPLACEMENT);
  add_util_class("self-baseline", ".%s {align-self: baseline;}",
                 NO_REPLACEMENT);
  add_util_class("!self-baseline", ".%s {align-self: baseline !important;}",
                 NO_REPLACEMENT);

  add_util_class("items-start", ".%s {align-items: flex-start;}",
                 NO_REPLACEMENT);
  add_util_class("!items-start", ".%s {align-items: flex-start !important;}",
                 NO_REPLACEMENT);
  add_util_class("items-end", ".%s {align-items: flex-end;}", NO_REPLACEMENT);
  add_util_class("!items-end", ".%s {align-items: flex-end !important;}",
                 NO_REPLACEMENT);
  add_util_class("items-center", ".%s {align-items: center;}", NO_REPLACEMENT);
  add_util_class("!items-center", ".%s {align-items: center !important;}",
                 NO_REPLACEMENT);
  add_util_class("items-baseline", ".%s {align-items: baseline;}",
                 NO_REPLACEMENT);
  add_util_class("!items-baseline", ".%s {align-items: baseline !important;}",
                 NO_REPLACEMENT);
  add_util_class("items-stretch", ".%s {align-items: stretch;}",
                 NO_REPLACEMENT);
  add_util_class("!items-stretch", ".%s {align-items: stretch !important;}",
                 NO_REPLACEMENT);

  // grid
  add_util_class("grid-rows-1",
                 ".%s {grid-template-rows: repeat(1, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-rows-1",
      ".%s {grid-template-rows: repeat(1, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-rows-2",
                 ".%s {grid-template-rows: repeat(2, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-rows-2",
      ".%s {grid-template-rows: repeat(2, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-rows-3",
                 ".%s {grid-template-rows: repeat(3, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-rows-3",
      ".%s {grid-template-rows: repeat(3, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-rows-4",
                 ".%s {grid-template-rows: repeat(4, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-rows-4",
      ".%s {grid-template-rows: repeat(4, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-rows-5",
                 ".%s {grid-template-rows: repeat(5, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-rows-5",
      ".%s {grid-template-rows: repeat(5, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-rows-6",
                 ".%s {grid-template-rows: repeat(6, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-rows-6",
      ".%s {grid-template-rows: repeat(6, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-rows-7",
                 ".%s {grid-template-rows: repeat(7, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-rows-7",
      ".%s {grid-template-rows: repeat(7, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-rows-8",
                 ".%s {grid-template-rows: repeat(8, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-rows-8",
      ".%s {grid-template-rows: repeat(8, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-rows-9",
                 ".%s {grid-template-rows: repeat(9, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-rows-9",
      ".%s {grid-template-rows: repeat(9, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-rows-10",
                 ".%s {grid-template-rows: repeat(10, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-rows-10",
      ".%s {grid-template-rows: repeat(10, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-rows-11",
                 ".%s {grid-template-rows: repeat(11, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-rows-11",
      ".%s {grid-template-rows: repeat(11, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-rows-12",
                 ".%s {grid-template-rows: repeat(12, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-rows-12",
      ".%s {grid-template-rows: repeat(12, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-rows-none", ".%s {grid-template-rows: none;}",
                 NO_REPLACEMENT);
  add_util_class("!grid-rows-none",
                 ".%s {grid-template-rows: none !important;}", NO_REPLACEMENT);
  add_util_class("grid-rows-subgrid", ".%s {grid-template-rows: subgrid;}",
                 NO_REPLACEMENT);
  add_util_class("!grid-rows-subgrid",
                 ".%s {grid-template-rows: subgrid !important;}",
                 NO_REPLACEMENT);

  add_util_class("grid-cols-1",
                 ".%s {grid-template-columns: repeat(1, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-cols-1",
      ".%s {grid-template-columns: repeat(1, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-cols-2",
                 ".%s {grid-template-columns: repeat(2, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-cols-2",
      ".%s {grid-template-columns: repeat(2, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-cols-3",
                 ".%s {grid-template-columns: repeat(3, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-cols-3",
      ".%s {grid-template-columns: repeat(3, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-cols-4",
                 ".%s {grid-template-columns: repeat(4, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-cols-4",
      ".%s {grid-template-columns: repeat(4, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-cols-5",
                 ".%s {grid-template-columns: repeat(5, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-cols-5",
      ".%s {grid-template-columns: repeat(5, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-cols-6",
                 ".%s {grid-template-columns: repeat(6, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-cols-6",
      ".%s {grid-template-columns: repeat(6, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-cols-7",
                 ".%s {grid-template-columns: repeat(7, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-cols-7",
      ".%s {grid-template-columns: repeat(7, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-cols-8",
                 ".%s {grid-template-columns: repeat(8, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-cols-8",
      ".%s {grid-template-columns: repeat(8, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-cols-9",
                 ".%s {grid-template-columns: repeat(9, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-cols-9",
      ".%s {grid-template-columns: repeat(9, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-cols-10",
                 ".%s {grid-template-columns: repeat(10, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-cols-10",
      ".%s {grid-template-columns: repeat(10, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-cols-11",
                 ".%s {grid-template-columns: repeat(11, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-cols-11",
      ".%s {grid-template-columns: repeat(11, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-cols-12",
                 ".%s {grid-template-columns: repeat(12, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-cols-12",
      ".%s {grid-template-columns: repeat(12, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-cols-none", ".%s {grid-template-columns: none;}",
                 NO_REPLACEMENT);
  add_util_class("!grid-cols-none",
                 ".%s {grid-template-columns: none !important;}",
                 NO_REPLACEMENT);
  add_util_class("grid-cols-subgrid", ".%s {grid-template-columns: subgrid;}",
                 NO_REPLACEMENT);
  add_util_class("!grid-cols-subgrid",
                 ".%s {grid-template-columns: subgrid !important;}",
                 NO_REPLACEMENT);

  add_util_class("row-auto", ".%s {grid-row: auto;}", NO_REPLACEMENT);
  add_util_class("!row-auto", ".%s {grid-row: auto !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-span-1", ".%s {grid-row: span 1 / span 1;}",
                 NO_REPLACEMENT);
  add_util_class("!row-span-1", ".%s {grid-row: span 1 / span 1 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-span-2", ".%s {grid-row: span 2 / span 2;}",
                 NO_REPLACEMENT);
  add_util_class("!row-span-2", ".%s {grid-row: span 2 / span 2 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-span-3", ".%s {grid-row: span 3 / span 3;}",
                 NO_REPLACEMENT);
  add_util_class("!row-span-3", ".%s {grid-row: span 3 / span 3 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-span-4", ".%s {grid-row: span 4 / span 4;}",
                 NO_REPLACEMENT);
  add_util_class("!row-span-4", ".%s {grid-row: span 4 / span 4 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-span-5", ".%s {grid-row: span 5 / span 5;}",
                 NO_REPLACEMENT);
  add_util_class("!row-span-5", ".%s {grid-row: span 5 / span 5 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-span-6", ".%s {grid-row: span 6 / span 6;}",
                 NO_REPLACEMENT);
  add_util_class("!row-span-6", ".%s {grid-row: span 6 / span 6 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-span-7", ".%s {grid-row: span 7 / span 7;}",
                 NO_REPLACEMENT);
  add_util_class("!row-span-7", ".%s {grid-row: span 7 / span 7 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-span-8", ".%s {grid-row: span 8 / span 8;}",
                 NO_REPLACEMENT);
  add_util_class("!row-span-8", ".%s {grid-row: span 8 / span 8 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-span-9", ".%s {grid-row: span 9 / span 9;}",
                 NO_REPLACEMENT);
  add_util_class("!row-span-9", ".%s {grid-row: span 9 / span 9 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-span-10", ".%s {grid-row: span 10 / span 10;}",
                 NO_REPLACEMENT);
  add_util_class("!row-span-10",
                 ".%s {grid-row: span 10 / span 10 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-span-11", ".%s {grid-row: span 11 / span 11;}",
                 NO_REPLACEMENT);
  add_util_class("!row-span-11",
                 ".%s {grid-row: span 11 / span 11 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-span-12", ".%s {grid-row: span 12 / span 12;}",
                 NO_REPLACEMENT);
  add_util_class("!row-span-12",
                 ".%s {grid-row: span 12 / span 12 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-span-full", ".%s {grid-row: 1 / -1;}", NO_REPLACEMENT);
  add_util_class("!row-span-full", ".%s {grid-row: 1 / -1 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-start-1", ".%s {grid-row-start: 1;}", NO_REPLACEMENT);
  add_util_class("!row-start-1", ".%s {grid-row-start: 1 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-start-2", ".%s {grid-row-start: 2;}", NO_REPLACEMENT);
  add_util_class("!row-start-2", ".%s {grid-row-start: 2 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-start-3", ".%s {grid-row-start: 3;}", NO_REPLACEMENT);
  add_util_class("!row-start-3", ".%s {grid-row-start: 3 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-start-4", ".%s {grid-row-start: 4;}", NO_REPLACEMENT);
  add_util_class("!row-start-4", ".%s {grid-row-start: 4 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-start-5", ".%s {grid-row-start: 5;}", NO_REPLACEMENT);
  add_util_class("!row-start-5", ".%s {grid-row-start: 5 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-start-6", ".%s {grid-row-start: 6;}", NO_REPLACEMENT);
  add_util_class("!row-start-6", ".%s {grid-row-start: 6 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-start-7", ".%s {grid-row-start: 7;}", NO_REPLACEMENT);
  add_util_class("!row-start-7", ".%s {grid-row-start: 7 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-start-8", ".%s {grid-row-start: 8;}", NO_REPLACEMENT);
  add_util_class("!row-start-8", ".%s {grid-row-start: 8 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-start-9", ".%s {grid-row-start: 9;}", NO_REPLACEMENT);
  add_util_class("!row-start-9", ".%s {grid-row-start: 9 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-start-10", ".%s {grid-row-start: 10;}", NO_REPLACEMENT);
  add_util_class("!row-start-10", ".%s {grid-row-start: 10 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-start-11", ".%s {grid-row-start: 11;}", NO_REPLACEMENT);
  add_util_class("!row-start-11", ".%s {grid-row-start: 11 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-start-12", ".%s {grid-row-start: 12;}", NO_REPLACEMENT);
  add_util_class("!row-start-12", ".%s {grid-row-start: 12 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-start-13", ".%s {grid-row-start: 13;}", NO_REPLACEMENT);
  add_util_class("!row-start-13", ".%s {grid-row-start: 13 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-start-auto", ".%s {grid-row-start: auto;}",
                 NO_REPLACEMENT);
  add_util_class("!row-start-auto", ".%s {grid-row-start: auto !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-end-1", ".%s {grid-row-end: 1;}", NO_REPLACEMENT);
  add_util_class("!row-end-1", ".%s {grid-row-end: 1 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-end-2", ".%s {grid-row-end: 2;}", NO_REPLACEMENT);
  add_util_class("!row-end-2", ".%s {grid-row-end: 2 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-end-3", ".%s {grid-row-end: 3;}", NO_REPLACEMENT);
  add_util_class("!row-end-3", ".%s {grid-row-end: 3 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-end-4", ".%s {grid-row-end: 4;}", NO_REPLACEMENT);
  add_util_class("!row-end-4", ".%s {grid-row-end: 4 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-end-5", ".%s {grid-row-end: 5;}", NO_REPLACEMENT);
  add_util_class("!row-end-5", ".%s {grid-row-end: 5 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-end-6", ".%s {grid-row-end: 6;}", NO_REPLACEMENT);
  add_util_class("!row-end-6", ".%s {grid-row-end: 6 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-end-7", ".%s {grid-row-end: 7;}", NO_REPLACEMENT);
  add_util_class("!row-end-7", ".%s {grid-row-end: 7 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-end-8", ".%s {grid-row-end: 8;}", NO_REPLACEMENT);
  add_util_class("!row-end-8", ".%s {grid-row-end: 8 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-end-9", ".%s {grid-row-end: 9;}", NO_REPLACEMENT);
  add_util_class("!row-end-9", ".%s {grid-row-end: 9 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-end-10", ".%s {grid-row-end: 10;}", NO_REPLACEMENT);
  add_util_class("!row-end-10", ".%s {grid-row-end: 10 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-end-11", ".%s {grid-row-end: 11;}", NO_REPLACEMENT);
  add_util_class("!row-end-11", ".%s {grid-row-end: 11 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-end-12", ".%s {grid-row-end: 12;}", NO_REPLACEMENT);
  add_util_class("!row-end-12", ".%s {grid-row-end: 12 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-end-13", ".%s {grid-row-end: 13;}", NO_REPLACEMENT);
  add_util_class("!row-end-13", ".%s {grid-row-end: 13 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-end-auto", ".%s {grid-row-end: auto;}", NO_REPLACEMENT);
  add_util_class("!row-end-auto", ".%s {grid-row-end: auto !important;}",
                 NO_REPLACEMENT);

  add_util_class("col-auto", ".%s {grid-column: auto;}", NO_REPLACEMENT);
  add_util_class("!col-auto", ".%s {grid-column: auto !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-span-1", ".%s {grid-column: span 1 / span 1;}",
                 NO_REPLACEMENT);
  add_util_class("!col-span-1",
                 ".%s {grid-column: span 1 / span 1 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-span-2", ".%s {grid-column: span 2 / span 2;}",
                 NO_REPLACEMENT);
  add_util_class("!col-span-2",
                 ".%s {grid-column: span 2 / span 2 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-span-3", ".%s {grid-column: span 3 / span 3;}",
                 NO_REPLACEMENT);
  add_util_class("!col-span-3",
                 ".%s {grid-column: span 3 / span 3 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-span-4", ".%s {grid-column: span 4 / span 4;}",
                 NO_REPLACEMENT);
  add_util_class("!col-span-4",
                 ".%s {grid-column: span 4 / span 4 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-span-5", ".%s {grid-column: span 5 / span 5;}",
                 NO_REPLACEMENT);
  add_util_class("!col-span-5",
                 ".%s {grid-column: span 5 / span 5 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-span-6", ".%s {grid-column: span 6 / span 6;}",
                 NO_REPLACEMENT);
  add_util_class("!col-span-6",
                 ".%s {grid-column: span 6 / span 6 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-span-7", ".%s {grid-column: span 7 / span 7;}",
                 NO_REPLACEMENT);
  add_util_class("!col-span-7",
                 ".%s {grid-column: span 7 / span 7 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-span-8", ".%s {grid-column: span 8 / span 8;}",
                 NO_REPLACEMENT);
  add_util_class("!col-span-8",
                 ".%s {grid-column: span 8 / span 8 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-span-9", ".%s {grid-column: span 9 / span 9;}",
                 NO_REPLACEMENT);
  add_util_class("!col-span-9",
                 ".%s {grid-column: span 9 / span 9 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-span-10", ".%s {grid-column: span 10 / span 10;}",
                 NO_REPLACEMENT);
  add_util_class("!col-span-10",
                 ".%s {grid-column: span 10 / span 10 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-span-11", ".%s {grid-column: span 11 / span 11;}",
                 NO_REPLACEMENT);
  add_util_class("!col-span-11",
                 ".%s {grid-column: span 11 / span 11 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-span-12", ".%s {grid-column: span 12 / span 12;}",
                 NO_REPLACEMENT);
  add_util_class("!col-span-12",
                 ".%s {grid-column: span 12 / span 12 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-span-full", ".%s {grid-column: 1 / -1;}", NO_REPLACEMENT);
  add_util_class("!col-span-full", ".%s {grid-column: 1 / -1 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-start-1", ".%s {grid-column-start: 1;}", NO_REPLACEMENT);
  add_util_class("!col-start-1", ".%s {grid-column-start: 1 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-start-2", ".%s {grid-column-start: 2;}", NO_REPLACEMENT);
  add_util_class("!col-start-2", ".%s {grid-column-start: 2 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-start-3", ".%s {grid-column-start: 3;}", NO_REPLACEMENT);
  add_util_class("!col-start-3", ".%s {grid-column-start: 3 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-start-4", ".%s {grid-column-start: 4;}", NO_REPLACEMENT);
  add_util_class("!col-start-4", ".%s {grid-column-start: 4 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-start-5", ".%s {grid-column-start: 5;}", NO_REPLACEMENT);
  add_util_class("!col-start-5", ".%s {grid-column-start: 5 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-start-6", ".%s {grid-column-start: 6;}", NO_REPLACEMENT);
  add_util_class("!col-start-6", ".%s {grid-column-start: 6 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-start-7", ".%s {grid-column-start: 7;}", NO_REPLACEMENT);
  add_util_class("!col-start-7", ".%s {grid-column-start: 7 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-start-8", ".%s {grid-column-start: 8;}", NO_REPLACEMENT);
  add_util_class("!col-start-8", ".%s {grid-column-start: 8 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-start-9", ".%s {grid-column-start: 9;}", NO_REPLACEMENT);
  add_util_class("!col-start-9", ".%s {grid-column-start: 9 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-start-10", ".%s {grid-column-start: 10;}",
                 NO_REPLACEMENT);
  add_util_class("!col-start-10", ".%s {grid-column-start: 10 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-start-11", ".%s {grid-column-start: 11;}",
                 NO_REPLACEMENT);
  add_util_class("!col-start-11", ".%s {grid-column-start: 11 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-start-12", ".%s {grid-column-start: 12;}",
                 NO_REPLACEMENT);
  add_util_class("!col-start-12", ".%s {grid-column-start: 12 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-start-13", ".%s {grid-column-start: 13;}",
                 NO_REPLACEMENT);
  add_util_class("!col-start-13", ".%s {grid-column-start: 13 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-start-auto", ".%s {grid-column-start: auto;}",
                 NO_REPLACEMENT);
  add_util_class("!col-start-auto", ".%s {grid-column-start: auto !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-end-1", ".%s {grid-column-end: 1;}", NO_REPLACEMENT);
  add_util_class("!col-end-1", ".%s {grid-column-end: 1 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-end-2", ".%s {grid-column-end: 2;}", NO_REPLACEMENT);
  add_util_class("!col-end-2", ".%s {grid-column-end: 2 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-end-3", ".%s {grid-column-end: 3;}", NO_REPLACEMENT);
  add_util_class("!col-end-3", ".%s {grid-column-end: 3 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-end-4", ".%s {grid-column-end: 4;}", NO_REPLACEMENT);
  add_util_class("!col-end-4", ".%s {grid-column-end: 4 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-end-5", ".%s {grid-column-end: 5;}", NO_REPLACEMENT);
  add_util_class("!col-end-5", ".%s {grid-column-end: 5 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-end-6", ".%s {grid-column-end: 6;}", NO_REPLACEMENT);
  add_util_class("!col-end-6", ".%s {grid-column-end: 6 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-end-7", ".%s {grid-column-end: 7;}", NO_REPLACEMENT);
  add_util_class("!col-end-7", ".%s {grid-column-end: 7 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-end-8", ".%s {grid-column-end: 8;}", NO_REPLACEMENT);
  add_util_class("!col-end-8", ".%s {grid-column-end: 8 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-end-9", ".%s {grid-column-end: 9;}", NO_REPLACEMENT);
  add_util_class("!col-end-9", ".%s {grid-column-end: 9 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-end-10", ".%s {grid-column-end: 10;}", NO_REPLACEMENT);
  add_util_class("!col-end-10", ".%s {grid-column-end: 10 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-end-11", ".%s {grid-column-end: 11;}", NO_REPLACEMENT);
  add_util_class("!col-end-11", ".%s {grid-column-end: 11 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-end-12", ".%s {grid-column-end: 12;}", NO_REPLACEMENT);
  add_util_class("!col-end-12", ".%s {grid-column-end: 12 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-end-13", ".%s {grid-column-end: 13;}", NO_REPLACEMENT);
  add_util_class("!col-end-13", ".%s {grid-column-end: 13 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-end-auto", ".%s {grid-column-end: auto;}",
                 NO_REPLACEMENT);
  add_util_class("!col-end-auto", ".%s {grid-column-end: auto !important;}",
                 NO_REPLACEMENT);

  // gap
  add_util_class("gap", ".%s {gap: %s;}", SINGLE_REPLACEMENT);
  add_util_class("!gap", ".%s {gap: %s !important;}", SINGLE_REPLACEMENT);

  // tables
  add_util_class("table-auto", ".%s {table-layout: auto;}", SINGLE_REPLACEMENT);
  add_util_class("!table-auto", ".%s {table-layout: auto !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("table-fixed", ".%s {table-layout: fixed;}",
                 SINGLE_REPLACEMENT);
  add_util_class("!table-fixed", ".%s {table-layout: fixed !important;}",
                 SINGLE_REPLACEMENT);

  // boxes
  add_util_class("float-start", ".%s {float: inline-start;}",
                 SINGLE_REPLACEMENT);
  add_util_class("!float-start", ".%s {float: inline-start !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("float-end", ".%s {float: inline-end;}", SINGLE_REPLACEMENT);
  add_util_class("!float-end", ".%s {float: inline-end !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("float-right", ".%s {float: right;}", SINGLE_REPLACEMENT);
  add_util_class("!float-right", ".%s {float: right !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("float-left", ".%s {float: left;}", SINGLE_REPLACEMENT);
  add_util_class("!float-left", ".%s {float: left !important;}",
                 SINGLE_REPLACEMENT);
  add_util_class("float-none", ".%s {float: none;}", SINGLE_REPLACEMENT);
  add_util_class("!float-none", ".%s {float: none !important;}",
                 SINGLE_REPLACEMENT);
}

void cwind_destroy() {
  regfree(utility_class_pattern);
  regfree(numerical_utility_class_value_pattern);
}

////////////////////////////////////////////////////////////////
//////////////////////  The Actual Juice  //////////////////////
////////////////////////////////////////////////////////////////
