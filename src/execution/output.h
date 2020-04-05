#include <stdbool.h>
/*TODO remove this 100 limit */
typedef struct Output
{
  char* stderr;
  char* stdout;
  int status;
  double* times;
} Output;



