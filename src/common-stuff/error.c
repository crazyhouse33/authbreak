#include "error.h"
#include "concat_string.h"
#include <errno.h>
#include <stdarg.h> //variadic stuff
#include <stdio.h>  //perror
#include <stdlib.h> //abort
#include <string.h> //strerror

void critical_error_msg(char *format, ...) {
  char *lib_error = strerror(errno);
  char *new_format = get_concatenation_string("CRITICAL ERROR: ", format);
  va_list args;
  va_start(args, format);
  vfprintf(stderr, new_format, args);
  va_end(args);
  if (errno != 0)
    fprintf(stderr, "\nperror: %s\n", lib_error);
  abort();
}

void controlled_error_msg(int status, char *format, ...) {
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
  exit(status);
}
