#include <stdbool.h>
/*TODO remove this 100 limit */
typedef struct Option
{
  char* key;                
  char*  prompt[100];
  char* sucess[100];
  char* fail[100];
  int prompt_cpt, fail_cpt, sucess_cpt;
  bool no_timing, no_guessing, no_random;
  double wait, random_wait;

} Option;


Handler parse_injection_template (char* template_string);
/* Return the appropriate handler for the templates*/

