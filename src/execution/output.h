#include <stddef.h>//size_t
typedef struct Output
{
  char* out;
  int status;
  double times;
} Output;


Output* Output_new();
/*Return an correctly initialized Ouput in regard to the buffer size*/
size_t read_append_into_Output( int fd, Output* out, size_t* current_size );
/*Append the result in the output buffer and manage size properly(actualize constructor new default size, prevent overflow...*/



