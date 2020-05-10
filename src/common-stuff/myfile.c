#include "myfile.h"
#include <stdio.h>
#include <string.h>//strcpy
#include "stdlib.h"//free


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
  char *path = strncpy(path, path_begin, until);
  bool res = is_openable_file(path);
  free(path);
  return res;
}
