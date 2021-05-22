#include "argv.h" //get envp
#include "commandbuild.h"
#include "executor.h"
#include "interface/cliparser.h"
#include "timer.h"
#include <stdio.h>
// TODO manager class
static bool manage_output(Output *output, Or_combined_classifier *classifier, Command_builder* builder, bool early_stop) {
  if (or_combined_classifier_classify_output(classifier, output)) {
    puts("Found succefull creds:\n");
    puts(command_builder_current_command(builder));
    if (early_stop)
    	exit(0);
    return true;
  }
  return false;
}

int main(int argc, char *argv[]) {
  unsigned long resolution = init_timer(); // This is needed for APLE
  // getting arg
  Arguments *argument = get_arguments(argc, argv, 0);
  // setting backend accordingly
  Or_combined_classifier *classifier = argument->classifier_combined;
  Command_builder* builder= command_builder_new(argument->command_line, argument->prompt);
  Output *output = Output_new();
  char **current_envp = get_current_envp();
  bool at_least_one= false;
  executor_prepare(builder->argv, argument->wait, argument->random_wait, argument->prompt_wait, argument->prompt_random_wait);
  do {
    executor_get_output(builder->argv, builder->prompts, current_envp, 0, output);
    at_least_one |= manage_output(output, classifier, builder, argument->early_stop);

  } while (!command_builder_next_command(builder));
  puts("Ran out of possible tries");

  return argument->allow_miss == false && ! at_least_one;
}
