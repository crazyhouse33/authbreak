#include "cliparser.h"
#include "default_options.h"
#include "error.h"
#include "handler_front.h"
#include "or_combined_classifier.h"
#include "output_classifier_front.h"
#include <argp.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

#define TIMING_FAKE_KEY 1000
#define GUESSING_FAKE_KEY 1001
#define RANDOM_FAKE_KEY 1002
#define OR_FAKE_KEY 1003
#define NOT_FAKE_KEY 1004
#define DEFAULT_CHARSET_KEY 1005
#define DEFAULT_MAX_LEN_KEY 1006
#define DEFAULT_MIN_LEN_KEY 1007
#define DEFAULT_SEPARATOR_KEY 1008

const char *argp_program_version = AUTHBREAK_VERSION; // This variable is added at compilation
error_t argp_err_exit_status = 2;

static unsigned short parse_len(char *len_str) {
  unsigned long len = parse_positive_int_intolerant(len_str, 2, "Parsing Error: Specified default len \"%s\" is not a positive integer");
  if (len > USHRT_MAX)
    controlled_error_msg(2, "PARSING ERROR: Specified default len \"%h\" is too big.  Choose an integer between 0 and 65535", len);
  return (unsigned short)len;
}

/* Program documentation. */
char doc[] =
    "An exemple of a COMMAND: 'auth_command --user INJECT --password INJECT'\n\n"
    "INJECT: {MAIN[,OPT,...OPT]}\n\n"
    "Every injection point defines a set of strings that are going to replace the part in between {}. The brutforcer run every possible combinaison between your injection points only once.\n\n"
    "There are two type of injection points, you can force the type with OPT= type=file or type=iterator\n\n"
    "	1: File\n"
    "		MAIN is a path to an openable file. The guess are the ones present in the file, delimited by the the separator option\n\n"
    "		Valids OPT:\n"
    "			-separator=CHAR : Set the separator of the file\n"
    "	2: Iterator(default)\n"
    "		MAIN is empty, or in the form [NUM:]NUM. The second form set the sizes of every guess to be greater or equal than the first one and lesser or equal than the "
    "second one. If 0, the empty string is included in the guesses.\n\n"
    " 		Valids OPT:\n"
    "			-charset=STR : STR is a string of different characters. Every guess will contain only thoses characters.\n\n Exit Status:\n"
    "    0 If at least a try had been successfull.\n"
    "    1 The attack terminated without finding any sucessfull creds.\n"
    "    2 There is an error of parsing.\n"
    "    3 One of the ressource authbreak needs for the given command is not accessible (file, executable...)\n\n";
/* A description of the arguments we accept. */
char args_doc[] = "COMMAND";

/* The options we understand. */
struct argp_option options[] = {
    {0, 'h', 0, OPTION_HIDDEN, "Alias for --help", 0},
    {0, 0, 0, 0, "Injection Point Default Control:", 1},
    {
        "default-charset", DEFAULT_CHARSET_KEY, "CHARSET", 0, "Given charset become the default for every injection point. Default=abcdefghiklmnopqrstuvwxyz1234567890",
    },
    {"default-separator", DEFAULT_SEPARATOR_KEY, "SEP", 0, "Given char become the default separator for every injection point. Default=\\n", 1},
    {"default-len-min", DEFAULT_MIN_LEN_KEY, "INT", 0, "Given positive int become the default min_len for every injection point. Default=0", 1},
    {"default-len-max", DEFAULT_MAX_LEN_KEY, "INT", 0, "Given positive int become the default max_len for every injection point. Default=MAXUINT", 1},
    {0, 0, 0, 0, "Attack Controle Options:", 2},
    //{"no-timing", TIMING_FAKE_KEY, 0, 0, "Skip the timing attack phase.", 2},
    //  {"no-guessing", GUESSING_FAKE_KEY, 0, 0, "Skip the guessing attack phase.", 2},
    //    {"timout", 't', "NANOSECONDS", 0, "Stop execution if time is too long. This does not automatically classify it to fail. The classifiers are run against the output afterward, and the
    //    execution time is set to the timout. Be aware of that whith your times classifiers.", 2},
    {"prompt", 'p', "PAYLOAD", 0, "Authbreak injects this payload if he encounters a prompt. PAYLOAD can contain injection points. If many prompt options are given, it injects the consecutives "
                                  "prompt payloads in the order you set them. "
                                  "Nothing more than you write is injected. In particular, you have to add a newline where you want it to be entered.",
     2},
    {0, 0, 0, 0, "Output Interpretation Options:", 3},
    {"success", 's', "[!]CLASSIFIER_KEY OPERATOR VALUE", 0,
     "Add a CLASSIFIER to the current group of classifier. Authbreak considers a group TRUE if all of the CLASSIFIERS of the group are TRUE. Authbreak "
     "considers a try as a success if one group is TRUE. See NOT and OR options."
     " if there is no CLASSIFIER, every guess is a fail. If prefixed by !, the CLASSIFIER are negated. The possible CLASSIFIER_KEY are:",
     3},
    {0, 0, 0, 0, "	out_eq [!=,==] STR: The WHOLE SESSION stdout from the targeted process exactly matches STR", 4},
    {0, 0, 0, 0, "	time [<=,<,>=,>] NANOSECONDS: The total execution time of the targeted process respects the given operator and time.", 4},
    {0, 0, 0, 0, "	status [==,!=,<=,<,>=,>] INT: The exit status of the targeted process respects the given operator and status.", 4},
    {"NOT", NOT_FAKE_KEY, 0, 0, "Negate the next group of classifier.", 4},
    {"OR", OR_FAKE_KEY, 0, 0, "Create a new group of classifier.", 4},
    /*{0, 0, 0, 0, "Furtivity tuning options:", 6},
      {"wait", 'w', "SECONDS", 0, "Delay each guess by a certain amount of seconds.", 6},
      {"wait-prompt", 0, "SECONDS", 0, "Delay each prompt by a certain amount of seconds.", 6},
      {"random-wait", 0, "SECONDS", 0, "Delay each prompt by a random amount of seconds bounded by the entered value.", 6},
      {"random-wait", 'r', "SECONDS", 0, "Delay each guess by a random amount of seconds bounded by the entered value.", 6},
      {"no-random", RANDOM_FAKE_KEY, 0, 0, "Without this option, Authbreak makes the order of the guesses look random. Activate this flag to turn off this behaviour to win some time.", 6},
      {0, 0, 0, 0, "User interface", 7},
      {0, 0, 0, 0, "Press any key to print infos about the state (step of attack, number of guesses done, number yet to be done...)", 7},
      {"no-session", 0, 0, 0, "When running, at any interuption (user or crash, authbreak saves his current state. If you invoke it with the exact same commandline, it will load his old session. This
      flag forbids loading an old session. THE OLD SESSION WILL BE OVERWRITTEN", 7},
      */

    {0, 0, 0, 0, "Others Options:", 10},

    {0}};

int arg_count = 0; // this should be static to parse_opt. But it fail if we parse more than one time. So we put it global, for the test to be able to pass
/* Arg parser */
static error_t parse_opt(int key, char *arg, struct argp_state *state) {
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  Arguments *arguments = state->input;

  switch (key) {
  case 's':
    if (arguments->current_classifier == NULL)
      arguments->current_classifier = composed_classifier_new(arguments->target);
    parse_classifier_str(arguments->current_classifier, arg);
    break;

  case OR_FAKE_KEY:
    if (arguments->current_classifier != NULL) { // there is at least one sucess in the group
      or_combined_classifier_add(arguments->classifier_combined, arguments->current_classifier);
      arguments->target = true;
      arguments->current_classifier = NULL;
    }

    break;
  case NOT_FAKE_KEY:
    if (arguments->current_classifier != NULL) // non empty composed classifier
      argp_failure(state, 2, 0, "Option --NOT can only start a classifier group, use --OR --NOT");

    arguments->target = false;
    break;
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

  case 'h':
    argp_state_help(state, state->err_stream, ARGP_HELP_STD_HELP);
    break;

  case ARGP_KEY_ARG:
    arguments->command_line = arg;
    arg_count++;

    break;

  case DEFAULT_MAX_LEN_KEY:
    DEFAULT_LEN_MAX = parse_len(arg);
    ;
    break;

  case DEFAULT_MIN_LEN_KEY:
    DEFAULT_LEN_MIN = parse_len(arg);
    break;

  case DEFAULT_SEPARATOR_KEY:
    DEFAULT_SEPARATOR = handler_parse_separator(arg, strlen(arg));
    break;

  case DEFAULT_CHARSET_KEY:
    DEFAULT_CHARSET = arg;

  case ARGP_KEY_END: {
    if (arguments->current_classifier != NULL) // we finished with a non empty composed class
      or_combined_classifier_add(arguments->classifier_combined, arguments->current_classifier);

    printf("\n");
    if (arg_count != 1) {
      argp_usage(state);
      argp_failure(state, 2, 0, "Authbreak take one and only one COMMAND positionnal argument argument. Got %d", arg_count);
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
  arguments->target = true;

  arguments->classifier_combined = or_combined_classifier_new();

  /* Parse our arguments; every option seen by parse_opt will
     be reflected in arguments. */

  arg_count = 0; // we reset state (for tests)

  // Set default default injection point
  DEFAULT_CHARSET = "abcdefghijklmnopqrstuvwxyz0123456789";
  DEFAULT_LEN_MIN = 0;
  DEFAULT_LEN_MAX = 8;
  DEFAULT_SEPARATOR = '\n';

  argp_parse(&argp, argc, argv, argp_flag, 0, arguments);

  return arguments;
}
