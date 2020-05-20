#include "cliparser.h"
#include "default_options.h"
#include <argp.h>
#include <stdbool.h>
#include <stdlib.h>

#define TIMING_FAKE_KEY 1000
#define GUESSING_FAKE_KEY 1001
#define RANDOM_FAKE_KEY 1002

const char *argp_program_version = "authbreak " AUTHBREAK_VERSION; // This variable is added at compilation

/* Program documentation. */
char doc[] = "\nAuthbreak version " AUTHBREAK_VERSION ":\n\nGeneric command line injection point based authentification brutforcer.";

/* A description of the arguments we accept. */
char args_doc[] = "COMMANDLINE";

/* The options we understand. */
struct argp_option options[] = {
    {0, 'h', 0, OPTION_HIDDEN, "Alias for --help", 0},
    {0, 0, 0, 0, "Attack Controle Options:", 1},
    {"no-timing", TIMING_FAKE_KEY, 0, 0, "Skip the timing attack phase.", 1},
    {"no-guessing", GUESSING_FAKE_KEY, 0, 0, "Skip the guessing attack phase.", 1},
    {"prompt", 'p', "PAYLOAD", 0, "The tool inject this payload if he encounter a prompt. If many prompt options given, the tool inject subsecutives prompt payload at each encoutered prompt. ", 1},
    {0, 0, 0, 0, "Output Interpretation Options:", 2},
    {"fail", 'f', "STR", 0, "Specify a fail condition. If many fail condition given, the tool consider it's a fail if one of them is verified.", 2},
    {"success", 's', "STR", 0, "Specify a sucess condition. If many sucess condition given, the tool consider it's a sucess if all of the sucess conditions are verified and no fail condition is "
                               "verified. In any other case, it's a fail.",
     2},

    {0, 0, 0, 0, "Furtivity tuning options:", 3},
    {"wait", 'w', "SECONDS", 0, "Delay each guess by a certain amount of second.", 3},
    {"random-wait", 'r', "SECONDS", 0, "Delay each guess by a random amount of second borned by the entered value.", 3},
    {"no-random", RANDOM_FAKE_KEY, 0, 0, "Wihout this option this tool randomize the order of the guess. Activate to turn off this behaviour to win some time.", 3},

    {0, 0, 0, 0, "Others Options:", 4},

    {0}};

/* Arg parser */
static error_t parse_opt(int key, char *arg, struct argp_state *state) {
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  Arguments *arguments = state->input;
  static int arg_count = 0;

  switch (key) {
  case RANDOM_FAKE_KEY:
    arguments->no_random = true;
    break;
  case GUESSING_FAKE_KEY:
    arguments->no_guessing = true;
    break;
  case TIMING_FAKE_KEY:
    arguments->no_timing = true;
    break;
  case 'r':
    arguments->random_wait = atof(arg);
    break;
  case 'w':
    arguments->wait = atof(arg);
    break;
  case 'p':
    arguments->prompt[arguments->prompt_cpt++] = arg;
    break;
  case 's':
    arguments->sucess[arguments->sucess_cpt++] = arg;
    break;
  case 'f':
    arguments->fail[arguments->fail_cpt++] = arg;
    break;

  case 'h':
    argp_state_help(state, state->err_stream, ARGP_HELP_STD_HELP);
    break;

  case ARGP_KEY_ARG:
    arguments->command_line = arg;
    arg_count++;

    break;

  case ARGP_KEY_END: {
    printf("\n");
    if (arg_count != 1) {
      argp_usage(state);
      argp_failure(state, 1, 0, "Authbreak take one and only one COMMAND positionnal argument argument. Got %d", arg_count);
    }
  } break;

  default:
    return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

/* Our argp parser. */
struct argp argp = {options, parse_opt, args_doc, doc};

Arguments *get_arguments(int argc, char **argv, unsigned argp_flag) {
  Arguments *arguments = malloc(sizeof(Arguments));

  /* Default values. */
  arguments->no_timing = false;
  arguments->no_guessing = false;
  arguments->no_random = false;
  arguments->wait = 0;
  arguments->random_wait = 0;
  arguments->prompt_cpt = 0;
  arguments->fail_cpt = 0;
  arguments->sucess_cpt = 0;
  /* Parse our arguments; every option seen by parse_opt will
     be reflected in arguments. */

  argp_parse(&argp, argc, argv, argp_flag, 0, arguments);

  // TODO set with given user option if present
  DEFAULT_CHARSET = "abcdefghijklmnopqrstuvwxyz0123456789";
  DEFAULT_LEN_MIN = 0;
  DEFAULT_LEN_MAX = 8;
  DEFAULT_SEPARATOR = '\n';
  return arguments;
}
