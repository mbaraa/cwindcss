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
  int stat;
  size_t classes_count = 0;
  char **classes = cwind_extract_css_classes(input_html, &classes_count);
  char *output = "";
  for (size_t i = 0; i < classes_count; i++) {
    stat = regexec(__utility_class_pattern, classes[i], 0, NULL, 0);
    if (stat) {
      continue;
    }

    MatchData *num_classes = find_all_string_submatch(
        __numerical_utility_class_value_pattern, classes[i]);
    MatchData *num_pre_classes = find_all_string_submatch(
        __numerical_utility_class_predefined_pattern, classes[i]);
    MatchData *word_classes = find_all_string_submatch(
        __only_words_utility_class_value_pattern, classes[i]);

    /* size_t j = 0; */
    /* while (value[j].match != NULL) { */
    /* size_t j = 0; */
    /* while (value[j].match != NULL) { */
    /* if (value[0].match != NULL && strcmp(value[0].match, classes[i]) == 0) {
     */

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

    struct class_fmt_hash_item *css_class = get_util_class(class_id);
    css_class_definition =
        extract_css_class_definition(css_class, class_name, class_thing_value);

    if (css_class_definition == NULL) {
      continue;
    }

    output = concat(output, strdup(css_class_definition));
    output = concat(output, " ");
    free(css_class_definition);
    /* j++; */
    /* } */
  }
  output[strlen(output) - 1] = '\0';

  return output;
}

int cwind_read_files_rec(const char *path, const char *extension_filter,
                         char **out_buffer) {
  DIR *d;
  struct dirent *dir;
  struct stat path_stat;
  char full_path[256];
  FILE *current_file = NULL;

  d = opendir(path);

  if (d) {
    while ((dir = readdir(d)) != NULL) {
      if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
        continue;
      }

      snprintf(full_path, sizeof(full_path), "%s/%s", path, dir->d_name);

      if (stat(full_path, &path_stat) == 0) {
        if (S_ISREG(path_stat.st_mode) &&
            has_suffix(full_path, extension_filter)) {
          printf("processing: %s ", full_path);
          current_file = fopen(full_path, "r+");
          if (current_file == NULL) {
            puts("❌");
            continue;
          }
          char *smol_buffer = (char *)malloc(path_stat.st_size);
          fread(smol_buffer, path_stat.st_size, 1, current_file);
          size_t buf_len = strlen(*out_buffer);
          if (buf_len < path_stat.st_size) {
            *out_buffer = (char *)malloc(buf_len + path_stat.st_size);
          }
          strcat(*out_buffer, smol_buffer);
          puts("✅");
          /* fclose(current_file); */
        } else if (S_ISDIR(path_stat.st_mode)) {
          cwind_read_files_rec(full_path, extension_filter, out_buffer);
        }
      } else {
        perror("Error getting file status");
        return CWIND_ERROR;
      }
    }
    closedir(d);
  } else {
    perror("Error opening directory");
    return CWIND_ERROR;
  }

  return CWIND_OK;
}

int cwind_generate_output_css_file(const char *path,
                                   const char *extension_filter,
                                   const char *out_path) {
  char *buffer = (char *)malloc(1);
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
