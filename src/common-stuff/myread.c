#include "myread.h"
#include <stdio.h>  //getdelim
#include <stdlib.h> //realloc
#include <unistd.h> //read
/*Should have code and use evergrowing pointer*/
size_t read_append(int fd, char **buffer, size_t *string_size, size_t *buffer_max_size) {
  // we need another level of inderiction for buffer because we need to potentially change the value of the pointer to realloc result

  size_t old_max = *buffer_max_size;

  size_t new_readed = read(fd, *buffer + *string_size, *buffer_max_size - *string_size);
  if (new_readed <= 0) // end of file or error
    return new_readed;

  *string_size += new_readed;
  if (*string_size >= *buffer_max_size / 2) { // buffer start to be full
    *buffer_max_size *= 4;
    *buffer = realloc(*buffer, *buffer_max_size);
  }
  return new_readed;
}

ssize_t getdelim_tok(char **buffer, size_t *buffer_size, int sep, FILE *fp) {

  ssize_t res = getdelim(buffer, buffer_size, sep, fp);
  if (res != -1 && *buffer[res] == sep)
    buffer[res] = 0;
  return res;
}
