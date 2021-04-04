#include "argv.h" //get envp
#include "commandbuild.h"
#include "executor.h"
#include "interface/cliparser.h"
#include "timer.h"
#include <stdio.h>
static void manage_output(Output *output, Or_combined_classifier *classifier, Command_builder* builder) {
  if (or_combined_classifier_classify_output(classifier, output)) {
    puts("Found succefull creds:\n");
    puts(command_builder_current_command(builder));
    exit(0);
  }
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
  executor_prepare(builder->argv, argument->wait, argument->random_wait, argument->prompt_wait, argument->prompt_random_wait);
  do {
    executor_get_output(builder->argv, builder->prompts, current_envp, 0, output);
    manage_output(output, classifier, builder);

  } while (!command_builder_next_command(builder));
  puts("Ran out of possible tries");

  exit(argument->no_miss == false);
}
