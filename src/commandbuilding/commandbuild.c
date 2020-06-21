#include "commandbuild.h"
#include "argv.h"
#include "concat_string.h"
#include "handler.h" //Handler
#include "max.h"
#include "null_vec.h"       //concatenate_vector
#include "replace_string.h" //Placeholder

char **command_builder_prompt;
char **command_builder_argv;

// TODO Dont use pointer for less cache miss and deferences
typedef struct Template_unit {
  Placeholder *placeholder;
  Handler *handler;
} Template_unit;

// Fix state
Template_unit *templates; // Couple of handler, placeholder
ssize_t unit_num;         // number of couple ss because we do a -1 to map from size to index and it can be 0

void prepare_command_builder(char *command, char **prompts) {
  /*Gather all the templates, assign handlers, prepare the fix part, also check if session allready exist to continue it unstead of creating new one*/
  size_t command_size;
  command_builder_argv = arg_vector_from_string(command, &command_size);
  command_builder_prompt = prompts;
  Placeholder **placeholders = (Placeholder **)create_vector(0);

  // Getting every placeholders

  size_t it = 0;
  while (command_builder_argv[it]) {
    Placeholder **new_placeholders = placeholder_parse_string(&command_builder_argv[it++], '{', '}', '\\');
    unit_num = concatenate_vector((void ***)&placeholders, (void **)new_placeholders);
  }
  it = 0;

  while (command_builder_prompt[it]) {
    Placeholder **new_placeholders = placeholder_parse_string(&command_builder_prompt[it++], '{', '}', '\\');
    unit_num = concatenate_vector((void ***)&placeholders, (void **)new_placeholders);
  }

  // Setting the switching units
  if (unit_num != 0) {
    templates = malloc(sizeof(Template_unit) * unit_num);
    for (size_t i = 0; i < unit_num; i++) {
      templates[i].placeholder = placeholders[i];
      /*Creating handler according to wats in placeholder*/
      templates[i].handler = handler_new(*placeholders[i]->base_string + placeholders[i]->begin + 1, placeholders[i]->size_place - 2);
      /*Repalcing {} separators with real handler value*/
      placeholder_switch(templates[i].placeholder, handler_get_current(templates[i].handler));
    }
  } else { // if no template we put a dummy handler to avoid branching in next_command TODO dummy handler
    templates = malloc(sizeof(Template_unit));
    char *dummy_str = malloc(sizeof(char));
    Placeholder *dummy_place = placeholder_new(&dummy_str, dummy_str, dummy_str);
    templates[0].placeholder = dummy_place;
    templates[0].handler = get_dummy_handler();
  }
}

// TODO do a sneaky cartesian product along with furtivity option (change order to have change in each consecutive template
bool command_builder_next_command() { // Cartesian product
  Template_unit *current_template = templates;
  char *next_value = handler_next(current_template->handler);
  while (!next_value) { // the handler boucled once
    // reset the handler to begining
    placeholder_switch(current_template->placeholder, handler_get_current(current_template->handler));
    current_template++;
    if (current_template - templates > unit_num - 1) // everything had been done
      return true;
    next_value = handler_next(current_template->handler);
  }
  placeholder_switch(current_template->placeholder, next_value);
  return false;
}

char *command_builder_current_command() {
  char *command = join_argv(command_builder_argv, ' ');
  char *prompts = join_argv(command_builder_prompt, '\n');
  concat_string(&command, "\n");
  concat_string(&command, prompts);
  free(prompts);
  return command;
}

void command_builder_fix(size_t positions, char *fix);

char *command_builder_serialize();
/*Serialize the state*/

void *command_builder_unserialize(char *string);
/*Set the state as specified in string*/
