#include <stdlib.h>
#include <argp.h>
#include <stdbool.h>
#include "cliparser.h"

const int timing_fake_key=1000
const int guessing_fake_key=1001
const int random_fake_key=1002

const char *argp_program_version =
  "authbreak 0.0";


/* Program documentation. */
char doc[] =
  "Authbreak. Generic command line injection point based authentification brutforcer";

/* A description of the arguments we accept. */
char args_doc[] = "COMMANDLINE";

/* The options we understand. */
struct argp_option options[] = {

  { 0, 0, 0, 0, "Attack Controle Options:", -1},
  {"no-timing",    timing_fake_key, 0,      0,  "Skip the timing attack phase." },
  {"no-guessing",    guessing_fake_key, 0,      0,  "Skip the guessing attack phase." },
  { 0, 0, 0, 0, "Output Interpretation Options:", -1},
  {"fail",    'f', "STR",      0,  "Specify a fail condition. If many fail condition given, the tool consider it's a fail if one of them is verified." },
  {"sucess",    's', "STR",      0,  "Specify a sucess condition. If many sucess condition given, the tool consider it's a sucess if all of the sucess conditions are verified and no fail condition is verified. In any other case, it's a fail." },
  {"prompt",   'p', "PAYLOAD", 0,
   "The tool inject this payload if he encounter a prompt. If may prompt options given, the tool inject subsecutives prompt payload at each encoutered prompt. " },

  { 0, 0, 0, 0, "Furtivity tuning options:", -1},
{"wait",    'w', "SECONDS",      0,  "Delay each guess by a certain amount of second." },
{"random-wait",    'r', "SECONDS",      0,  "Delay each guess by a random amount of second borned by the entered value." },
{"no-random",    random_fake_key, 0,      0,  "Wihout this option this tool randomize the order of the guess. Activate to turn off this behaviour to win some time." },

  { 0 }
};


/* Arg parser */
static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  Arguments* arguments = state->input;

  switch (key)
    {
    case random_fake_key: 
      arguments->no_random = true;
      break;
    case guessing_fake_key:
      arguments->no_guessing = true;
      break;
    case timing_fake_key:
      arguments->no_timing = true;
      break;
    case 'r':
      arguments->random_wait=atof(arg);
      break;
    case 'w':
      arguments->wait= atof(arg);
    case 'p':
      arguments->prompt[arguments->prompt_cpt++]= arg;
    case 's':
      arguments->success[arguments->sucess_cpt++]= arg;
    case 'f':
      arguments->fail[arguments->fail_cpt++]= arg;
    
    case ARGP_KEY_ARG:
	arguments->commandLine = arg;

      break;

    case ARGP_KEY_END:
      {
	      printf ("\n"); 
	      if (*arg_count > 1) 
		      argp_failure (state, 1, 0, "Authbreakek take one argument"); 
	      else if (*arg_count < 1) 
		      argp_failure (state, 1, 0, "too many arguments"); }      break;

    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

/* Our argp parser. */
struct argp argp = { options, parse_opt, args_doc, doc };

Arguments*
get_arguments (int argc, char **argv)
{
  Arguments* arguments = malloc(sizeof(Arguments))

  /* Default values. */
  arguments->silent = 0;
  argument->no_timing = false;
  arguments->no_guessing = false;
  arguments->no_random = false;
  arguments->wait=0;
  arguments->random_wait=0;
  arguments->prompt_cpt=0;
  arguments->fail_cpt=0;
  arguments->sucess_cpt=0;

  /* Parse our arguments; every option seen by parse_opt will
     be reflected in arguments. */
  argp_parse (&argp, argc, argv, 0, 0, arguments);
  return arguments;
}
