#include "output.h"
#include <stddef.h>//size_t


void executor_prepare( char** argv, double delay_min, double delay_rand, double prompt_delay, double prompt_delay_rand);
/* Modify in plac the command to optimize the execution speed / the timing precision
 * For now, just exececute a path search to localize the binary to be ran
 *
 * Setup delayers
 * */

void executor_get_output_no_delay( char** command, char** prompt, char** envp, double timout, Output* output);
/*Execute the command and fill given Output structure. First element of command must be an executable binary (ie not a command). Timout is useless for now*/

void executor_get_output( char** command, char** prompt, char** envp, double timout, Output* output);
/*Get output and add artificial delay corresponding to the prepare call*/

