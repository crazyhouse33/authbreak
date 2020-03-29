/*TODO remove this 100 limit */
typedef struct arguments
{
  char* commandLine;                
  char* [100] prompt, fail, success;
  int prompt_cpt, fail_cpt, success_cpt;
  bool no_timing, no_guessing, no_random;
  double wait, random_wait;

} Arguments;


Arguments* get_arguments (int argc, char **argv);

