#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include "cwindcss.h"

bool has_suffix(const char *str, const char *suffix) {
  size_t str_len = strlen(str);
  size_t suffix_len = strlen(suffix);

  if (suffix_len > str_len) {
    return false;
  }

  return strcmp(str + str_len - suffix_len, suffix) == 0;
}

void list_files_recursively(const char *path, const char *extension_filter) {
  DIR *d;
  struct dirent *dir;
  struct stat path_stat;
  char full_path[256];

  d = opendir(path);

  if (d) {
    while ((dir = readdir(d)) != NULL) {
      if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
        continue;
      }

      snprintf(full_path, sizeof(full_path), "%s/%s", path, dir->d_name);

      if (stat(full_path, &path_stat) == 0) {
        if (S_ISREG(path_stat.st_mode)) {
          if (has_suffix(full_path, extension_filter)) {
            printf("%s\n", full_path);
          }
        } else if (S_ISDIR(path_stat.st_mode)) {
          list_files_recursively(full_path, extension_filter);
        }
      } else {
        perror("Error getting file status");
      }
    }
    closedir(d);
  } else {
    perror("Error opening directory");
  }
}

int main(int argc, char *argv[]) {
  list_files_recursively(".", ".html");
  return 0;
}
