#include "output.h"
#include <stddef.h>//size_t

void executor_prepare_argv ( char** argv);
/* Modify the command to optimize the execution speed / the timing precision
 * For now, just exececute a path search to localize the binary to be ran
 * */

void executor_get_output( char** command, char** prompt, char** envp, double timout, Output* output);
/*Execute the command and fill given Output structure. If take more than timout time return Output as it is at the moment. first element of command must be an executable binary (ie not a command)*/

Output* executor_store_output( char* command, char** prompt, double timout);
/*Execute the command and store the result in shared memory output pool.  */
