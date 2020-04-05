#include "output.h"

void executor_prepare ( char* command);
/* Prepare the command to optimize the execution speed / the timing precision...*/

Output executor_exec( char* command, char** prompt, double timout);
/*Execute the command and return structure defining what happened. If take more than timout time return Output as it is*/

