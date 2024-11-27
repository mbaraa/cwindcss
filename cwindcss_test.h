#ifndef _CWINDCSS_H
#define _CWINDCSS_H

#include <stddef.h>

#define CWIND_OK 0
#define CWIND_ERROR 1

void cwind_init();
void cwind_destroy();
char **cwind_extract_css_classes(char *html, size_t *out_classes_count);
char *cwind_process_utility_classes(char *input_html);
int cwind_read_files_rec(const char *path, const char *extension_filter,
                         char **out_buffer);
int cwind_generate_output_css_file(const char *path,
                                   const char *extension_filter,
                                   const char *out_path);

#endif // !_CWINDCSS_H
