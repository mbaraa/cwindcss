#include "cwindcss.h"
#include "regexes.h"
#include "strings.h"
#include "utility_classes.h"

#include <dirent.h>
#include <regex.h>
#include <stdio.h>
#include <sys/stat.h>

#include "boxes.h"
#include "display.h"
#include "flexbox.h"
#include "gap.h"
#include "grid.h"
#include "inset.h"
#include "order.h"
#include "position_placing.h"
#include "positioning.h"
#include "sizing.h"
#include "spacing.h"
#include "tables.h"

void cwind_init() {
  init_utility_classes();
  init_boxes_classes();
  init_display_classes();
  init_flexbox_classes();
  init_gap_classes();
  init_grid_classes();
  init_inset_classes();
  init_order_classes();
  init_position_placing_classes();
  init_positioning_classes();
  init_sizing_classes();
  init_spacing_classes();
  init_tables_classes();
}

void cwind_destroy() { destroy_utility_classes(); }

array *cwind_extract_css_classes(char *html) {
  const char *classes_pattern_str = "class=\"([^\"]+)\"";
  regex_t *classes_pattern = compile_regex(classes_pattern_str);

  size_t sz = 0;
  match_data *matches = find_all_string_submatch(classes_pattern, html, &sz);
  regfree(classes_pattern);
  free(classes_pattern);
  if (sz == 0) {
    return array_new(0, STRINGS);
  }

  char *all_classes = (char *)malloc(sizeof(char) * sz);
  if (sz > 0) {
    all_classes = strdup(matches[0].group1);
  }
  for (size_t i = 1; i < sz; i++) {
    char *tmp = concat(all_classes, " ");
    free(all_classes);
    all_classes = tmp;

    tmp = concat(all_classes, matches[i].group1);
    free(all_classes);
    all_classes = tmp;
  }
  destroy_matches_data(matches, sz);

  array *tokens = split_string(all_classes, " ");
  free(all_classes);
  if (tokens->len == 0) {
    array_destroy(tokens);
    return array_new(0, STRINGS);
  }

  struct str_bool_hash_item *unique_classes = NULL;
  ARRAY_ITER(tokens, token) {
    struct str_bool_hash_item *item = NULL;

    HASH_FIND_STR(unique_classes, token.string, item);
    if (item == NULL) {
      item = (struct str_bool_hash_item *)malloc(
          sizeof(struct str_bool_hash_item));
      item->key = strdup(token.string);
      item->value = true;
      HASH_ADD_STR(unique_classes, key, item);
    }
  }
  array_destroy(tokens);

  size_t num_classes = unique_classes == NULL ? 0 : HASH_COUNT(unique_classes);
  array *classes = array_new(num_classes, STRINGS);

  struct str_bool_hash_item *item = NULL, *tmp = NULL;
  int i = 0;
  HASH_ITER(hh, unique_classes, item, tmp) {
    array_set_string_at(classes, i++, item->key);
    HASH_DEL(unique_classes, item);
    free(item);
  }

  return classes;
}

// TODO: replace char* with buffer
char *cwind_process_utility_classes(char *input_html) {
  int stat;
  array *classes = cwind_extract_css_classes(input_html);

  char *output = strdup("");
  if (!output) {
    return NULL;
  }

  ARRAY_ITER(classes, class) {
    stat = regexec(__utility_class_pattern, class.string, 0, NULL, 0);
    if (stat) {
      continue;
    }

    size_t num_count = 0, pre_count = 0, word_count = 0;
    match_data *num_classes = find_all_string_submatch(
        __numerical_utility_class_value_pattern, class.string, &num_count);
    match_data *num_pre_classes = find_all_string_submatch(
        __numerical_utility_class_predefined_pattern, class.string, &pre_count);
    match_data *word_classes = find_all_string_submatch(
        __only_words_utility_class_value_pattern, class.string, &word_count);

    char *css_class_definition = NULL;
    char *class_id = NULL;
    char *class_name = NULL;
    char *class_thing_value = NULL;

    if (num_classes != NULL && num_classes[0].match != NULL) {
      class_id = num_classes[0].group1;
      class_thing_value = num_classes[0].group2;
      class_name = num_classes[0].match;
    } else if (num_pre_classes != NULL && num_pre_classes[0].match != NULL) {
      class_id = num_pre_classes[0].group1;
      class_thing_value = num_pre_classes[0].group2;
      class_name = num_pre_classes[0].match;
    } else if (word_classes != NULL && word_classes[0].match != NULL) {
      class_id = word_classes[0].group1;
      class_name = word_classes[0].match;
    }

    if (class_id == NULL) {
      goto free_things;
    }

    struct class_fmt_hash_item *css_class = get_util_class(class_id);
    css_class_definition =
        extract_css_class_definition(css_class, class_name, class_thing_value);

    if (css_class_definition == NULL) {
      goto free_things;
    }

    char *tmp = concat(output, css_class_definition);
    free(output);
    output = tmp;

    tmp = concat(output, " ");
    free(output);
    output = tmp;

  free_things:
    free(css_class_definition);
    destroy_matches_data(num_classes, num_count);
    destroy_matches_data(num_pre_classes, pre_count);
    destroy_matches_data(word_classes, word_count);
  }

  array_destroy(classes);

  size_t out_len = strlen(output);
  if (out_len > 0) {
    output[out_len - 1] = '\0';
  }

  return output;
}

int cwind_read_files_rec_impl(const char *path, const char *extension_filter,
                              char **out_buffer, size_t *buf_len,
                              size_t *buf_cap) {
  DIR *d;
  struct dirent *dir;
  struct stat path_stat;
  char full_path[512];
  FILE *current_file = NULL;

  d = opendir(path);
  if (!d) {
    perror("Error opening directory");
    return CWIND_ERROR;
  }

  while ((dir = readdir(d)) != NULL) {
    if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
      continue;
    }

    snprintf(full_path, sizeof(full_path), "%s/%s", path, dir->d_name);

    if (stat(full_path, &path_stat) != 0) {
      perror("Error getting file status");
      closedir(d);
      return CWIND_ERROR;
    }

    if (S_ISREG(path_stat.st_mode) && has_suffix(full_path, extension_filter)) {
      printf("processing: %s ", full_path);

      current_file = fopen(full_path, "rb");
      if (current_file == NULL) {
        puts("X");
        continue;
      }

      size_t file_size = path_stat.st_size;

      size_t required_space = *buf_len + file_size + 1;
      if (required_space > *buf_cap) {
        size_t new_cap = *buf_cap == 0 ? required_space * 2 : *buf_cap * 2;
        if (new_cap < required_space)
          new_cap = required_space;

        char *next_buf = (char *)realloc(*out_buffer, new_cap);
        if (!next_buf) {
          perror("Out of memory");
          fclose(current_file);
          closedir(d);
          return CWIND_ERROR;
        }
        *out_buffer = next_buf;
        *buf_cap = new_cap;
      }

      size_t bytes_read =
          fread(*out_buffer + *buf_len, 1, file_size, current_file);
      *buf_len += bytes_read;
      (*out_buffer)[*buf_len] = '\0';

      puts("✓");
      fclose(current_file);

    } else if (S_ISDIR(path_stat.st_mode)) {
      int res = cwind_read_files_rec_impl(full_path, extension_filter,
                                          out_buffer, buf_len, buf_cap);
      if (res != CWIND_OK) {
        closedir(d);
        return CWIND_ERROR;
      }
    }
  }

  closedir(d);
  return CWIND_OK;
}

int cwind_read_files_rec(const char *path, const char *extension_filter,
                         char **out_buffer) {
  size_t buf_len = 0;
  size_t buf_cap = 0;

  *out_buffer = NULL;

  return cwind_read_files_rec_impl(path, extension_filter, out_buffer, &buf_len,
                                   &buf_cap);
}

int cwind_generate_output_css_file(const char *path,
                                   const char *extension_filter,
                                   const char *out_path) {
  char *buffer = NULL;
  int stat = cwind_read_files_rec(path, extension_filter, &buffer);
  if (stat != CWIND_OK) {
    return stat;
  }
  size_t buffer_len = strlen(buffer);
  buffer[buffer_len - 1] = '\0';

  char *output_css = cwind_process_utility_classes(buffer);
  if (output_css == NULL) {
    return CWIND_ERROR;
  }

  FILE *f = fopen(out_path, "w+");
  if (f == NULL) {
    perror("can't create output file");
    return CWIND_ERROR;
  }

  size_t output_css_len = strlen(output_css);
  if (!fwrite(output_css, output_css_len, 1, f)) {
    return CWIND_ERROR;
  }

  free(output_css);
  /* free(buffer); */
  fclose(f);

  return CWIND_OK;
}
