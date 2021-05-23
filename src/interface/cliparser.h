#ifndef XX_INCLUDE_GUARD_CLIPARSER_H__XX
#define XX_INCLUDE_GUARD_CLIPARSER_H__XX
#include <stdbool.h>
#include "or_combined_classifier.h"
/*TODO remove this 100 limit */
typedef struct Arguments
{
  char* command_line;                
  char**  prompt;
  Or_combined_classifier* classifier_combined;
  bool no_timing, no_guessing, no_random;
  double wait, random_wait, prompt_wait, prompt_random_wait;//delayer
  bool target;
  bool allow_miss, early_stop;

  //state
  Composed_classifier* current_classifier;


} Arguments;


Arguments* get_arguments (int argc, char **argv, unsigned argp_flag);
#endif
