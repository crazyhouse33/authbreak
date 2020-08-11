#include "argv.h" //get envp
#include "commandbuild.h"
#include "executor.h"
#include "interface/cliparser.h"
#include "timer.h"
#include <stdio.h>
void manage_output(Output *output, Or_combined_classifier *classifier) {
  if (or_combined_classifier_classify_output(classifier, output)) {
    puts("Found succefull creds:\n");
    puts(command_builder_current_command());
    exit(0);
  }
}

int main(int argc, char *argv[]) {
  unsigned long resolution = init_timer(); // This is needed for APLE
  // getting arg
  Arguments *argument = get_arguments(argc, argv, 0);
  // setting backend accordingly
  Or_combined_classifier *classifier = argument->classifier_combined;
  prepare_command_builder(argument->command_line, argument->prompt);
  // TODO put it in a class that provide different function that use the executor interface, and call the appropriate stuff according to arguments

  char **current_envp = get_current_envp();
  executor_prepare_argv(command_builder_argv); // transforming command into absoluth path
  do {
    Output *output = executor_get_output(command_builder_argv, command_builder_prompt, argument->prompt_cpt, current_envp, 0);
    manage_output(output, classifier);

  } while (!command_builder_next_command());
  puts("Ran out of possible tries");

  exit(argument->no_miss == false);
}
