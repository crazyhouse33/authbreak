#include "argument_to_backend.h"
#include "argv.h" //get envp
#include "commandbuild.h"
#include "executor.h"
#include "interface/cliparser.h"
#include <stdio.h>
void manage_output(Output *output, Composed_classifier *classifier) {
  if (classify_output(classifier, output)) {
	  puts("Found succefull creds:\n");
    puts(command_builder_current_command());
    exit(0);
  }
}

int main(int argc, char *argv[]) {
  // getting arg
  Arguments *argument = get_arguments(argc, argv, 0);
  // setting backend accordingly
  Composed_classifier *classifier = arguments_to_composed_classifier(argument);
  prepare_command_builder(argument->command_line, argument->prompt);
  // TODO put it in a class that provide different function that use the executor interface, and call the appropriate stuff according to arguments

  char **current_envp = get_current_envp();
  executor_prepare_argv(command_builder_argv); // transforming command into absoluth path
  do {
    Output *output = executor_get_output(command_builder_argv, command_builder_prompt, argument->prompt_cpt, current_envp, 0);
    manage_output(output, classifier);

  } while (!command_builder_next_command());
  puts("Ran out of possible tries, no try match a succefful cred");
  exit(1);
}
