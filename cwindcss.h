#ifndef _CWINDCSS_H
#define _CWINDCSS_H

#include <regex.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uthash.h>

void cwind_init();
void cwind_destroy();
char **cwind_extract_css_classes(char *html, size_t *out_classes_count);
char *cwind_process_utility_classes(char *input_html);

#endif // !_CWINDCSS_H
