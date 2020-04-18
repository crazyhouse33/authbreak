#include "output.h"
#include "myread.h"
#include <stdlib.h>

size_t OUTPUT_BUFFER_SIZE = 4096;

Output *Output_new() {
  Output *res = malloc(sizeof(Output));
  res->out = malloc(sizeof(char) * OUTPUT_BUFFER_SIZE);
  res->out[0] = 0;
  return res;
}

size_t read_append_into_Output(int fd, Output *out, size_t *string_size) {
  /*Append the result in the output buffer and manage size properly(actualize constructor new default size, prevent overflow. Return the previous max value. So you can stop reading when after a call
   * returned value != string_size*/
  return read_append(fd, &out->out, string_size, &OUTPUT_BUFFER_SIZE);
}
