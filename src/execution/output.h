#ifndef XX__GUARD__OUTPUT_H_XX
#define XX__GUARD__OUTPUT_H_XX
#include <stddef.h>//size_t
typedef struct Output
{
  char* out;
  int exit_status;
  unsigned long term_time;
} Output;


Output* Output_new();
/*Return an correctly initialized Ouput in regard to the buffer size*/
size_t read_append_into_Output( int fd, Output* out );
/*Append the result in the output buffer and manage size properly(actualize constructor new default size, prevent overflow...*/
#endif
