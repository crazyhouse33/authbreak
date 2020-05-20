#include "file_info.h"
#include "stdlib.h" //free
#include <stdio.h>
#include <string.h> //strcpy

bool is_openable_file(char *path) {
  FILE *fp = fopen(path, "r");
  if (fp) {
    // exists
    fclose(fp);
    return true;
  }

  return false;
}

bool is_openable_file_until(char *path_begin, size_t until) {
  char old = path_begin[until];
  path_begin[until] = 0;
  bool res = is_openable_file(path_begin);
  path_begin[until] = old;
  return res;
}
