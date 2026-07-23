#include "utility_classes.h"
#include "regexes.h"

#include <regex.h>
#include <stdio.h>

regex_t *__utility_class_pattern = NULL;
regex_t *__numerical_utility_class_value_pattern = NULL;
regex_t *__numerical_utility_class_predefined_pattern = NULL;
regex_t *__only_words_utility_class_value_pattern = NULL;
struct class_fmt_hash_item *__classes_values = NULL;

regex_t *get_utility_class_pattern() { return __utility_class_pattern; }

void add_util_class(const char *uc, const char *fmt,
                    enum class_value_type type) {
  struct class_fmt_hash_item *s =
      (struct class_fmt_hash_item *)malloc(sizeof(struct class_fmt_hash_item));
  s->util_class = strdup(uc);
  s->fmt_str = strdup(fmt);
  s->type = type;
  HASH_ADD_STR(__classes_values, util_class, s);
}

struct class_fmt_hash_item *get_util_class(char *uc) {
  struct class_fmt_hash_item *util_class = NULL;

  HASH_FIND_STR(__classes_values, uc, util_class);
  if (util_class == NULL) {
    return NULL;
  }

  return util_class;
}

char *extract_css_class_definition(struct class_fmt_hash_item *css_class,
                                   char *class_name, char *value) {
  if (css_class == NULL || css_class->fmt_str == NULL) {
    return NULL;
  }

  size_t fmt_len = strlen(css_class->fmt_str);
  size_t class_name_len = strlen(class_name);

  char *css_class_name = (char *)malloc(class_name_len + 2);
  size_t j = 0;
  for (size_t i = 0; i < class_name_len; i++, j++) {
    char chr = class_name[i];
    if (!((chr >= 'a' && chr <= 'z') || (chr >= 'A' && chr <= 'Z') ||
          (chr >= '0' && chr <= '9') || chr == '-' || chr == '_')) {
      css_class_name[j] = '\\';
      css_class_name[++j] = chr;
      continue;
    }
    css_class_name[j] = chr;
  }
  css_class_name[j++] = '\0';
  css_class_name = realloc(css_class_name, j);

  char *css_class_definition = NULL;
  switch (css_class->type) {
  case NO_REPLACEMENT:
    css_class_definition = (char *)malloc(fmt_len + class_name_len);
    sprintf(css_class_definition, css_class->fmt_str, css_class_name);
    break;
  case SINGLE_REPLACEMENT:
    css_class_definition =
        (char *)malloc(fmt_len + class_name_len + (strlen(value)));
    sprintf(css_class_definition, css_class->fmt_str, css_class_name, value);
    break;
  case DOUBLE_REPLACEMENT:
    css_class_definition =
        (char *)malloc(fmt_len + class_name_len + (2 * strlen(value)));
    sprintf(css_class_definition, css_class->fmt_str, css_class_name, value,
            value);
    break;
  }

  return css_class_definition;
}

void init_utility_classes() {
  __utility_class_pattern = compile_regex(
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

  char numerical_utility_class_value_pattern_buffer[17 + sizing_classes_len];
  snprintf(numerical_utility_class_value_pattern_buffer,
           sizeof(numerical_utility_class_value_pattern_buffer),
           "(-?!?%s)-\\[(.*)\\]", sizing_classes);
  __numerical_utility_class_value_pattern =
      compile_regex(numerical_utility_class_value_pattern_buffer);

  char numerical_utility_class_predefined_pattern_buffer[20 +
                                                         sizing_classes_len];
  snprintf(numerical_utility_class_predefined_pattern_buffer,
           sizeof(numerical_utility_class_predefined_pattern_buffer),
           "(-?!?%s)-\\d+(\\.\\d+)?", sizing_classes);
  __numerical_utility_class_predefined_pattern =
      compile_regex(numerical_utility_class_predefined_pattern_buffer);

  __only_words_utility_class_value_pattern =
      compile_regex("^([\\-\\!a-z0-9-]+)$");
}

void destroy_classes_hash() {
  struct class_fmt_hash_item *class, *tmp;

  HASH_ITER(hh, __classes_values, class, tmp) {
    HASH_DEL(__classes_values, class);
    free(class->util_class);
    free(class->fmt_str);
    free(class);
  }
  free(tmp);
}

void destroy_utility_classes() {
  regfree(__utility_class_pattern);
  regfree(__numerical_utility_class_value_pattern);
  destroy_classes_hash();
}
