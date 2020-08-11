#ifndef XX_INCLUDE_GUARD_CLIPARSER_H__XX
#define XX_INCLUDE_GUARD_CLIPARSER_H__XX
#include <stdbool.h>
#include "or_combined_classifier.h"
/*TODO remove this 100 limit */
typedef struct Arguments
{
  char* command_line;                
  char*  prompt[100];
  Or_combined_classifier* classifier_combined;
  size_t prompt_cpt;
  bool no_timing, no_guessing, no_random;
  double wait, random_wait;

  //state
  Composed_classifier* current_classifier;
  bool target;
  bool no_miss;


} Arguments;


Arguments* get_arguments (int argc, char **argv, unsigned argp_flag);
#endif
