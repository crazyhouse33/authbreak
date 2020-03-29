#include <stdbool.h>
/*TODO remove this 100 limit */
typedef struct Arguments
{
  char* commandLine;                
  char*  prompt[100];
  char* sucess[100];
  char* fail[100];
  int prompt_cpt, fail_cpt, sucess_cpt;
  bool no_timing, no_guessing, no_random;
  double wait, random_wait;

} Arguments;


Arguments* get_arguments (int argc, char **argv);

