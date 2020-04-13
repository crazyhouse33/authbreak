#include "output.h"
#include <stddef.h>//size_t

void executor_prepare ( char* command);
/* Prepare the command to optimize the execution speed / the timing precision...*/

Output* executor_get_output( char* command, char** prompt, size_t prompt_number, double timout);
/*Execute the command and return structure defining what happened. If take more than timout time return Output as it is*/

Output* executor_store_output( char* command, char** prompt, double timout);
/*Execute the command and store the result in shared memory output pool.  */
