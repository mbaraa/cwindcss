#ifndef _UTILITY_CLASSES_H
#define _UTILITY_CLASSES_H

#include <regex.h>
#include <stdbool.h>
#include <uthash.h>

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

void add_util_class(const char *uc, const char *fmt,
                    enum class_value_type type);
struct class_fmt_hash_item *get_util_class(char *uc);
char *extract_css_class_definition(struct class_fmt_hash_item *css_class,
                                   char *class_name, char *value);

typedef void (*add_util_class_def)(char *uc, char *fmt,
                                   enum class_value_type type);

regex_t *get_utility_class_pattern();

void init_utility_classes();
void destroy_utility_classes();

#endif // _UTILITY_CLASSES_H
