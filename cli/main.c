#include "cwindcss.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    perror("usage:\n\tcwindcss <dir>");
    return 1;
  }

  cwind_init();

  int stat = cwind_generate_output_css_file(argv[1], ".html", "./cwind.css");
  if (stat != CWIND_OK) {
    perror("oopsie something went wrong");
    return 1;
  }

  cwind_destroy();

  return 0;
}
