#ifndef XX_INCLUDE_GUARD_CLIPARSER_H__XX
#define XX_INCLUDE_GUARD_CLIPARSER_H__XX
#include <stdbool.h>
/*TODO remove this 100 limit */
typedef struct Arguments
{
  char* command_line;                
  char*  prompt[100];
  char* sucess[100];
  int prompt_cpt, sucess_cpt;
  bool no_timing, no_guessing, no_random;
  double wait, random_wait;

} Arguments;


Arguments* get_arguments (int argc, char **argv, unsigned argp_flag);
#endif
