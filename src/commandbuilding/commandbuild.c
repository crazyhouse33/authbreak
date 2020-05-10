#include "commandbuild.h"
#include "argv.h"           //arg_vector_from_string
#include "handler.h"        //Handler
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
size_t unit_num;          // number of couple

// Dynamic state
long unsigned int iterator; // used for sessionning

/*This file is important optimization wise because it's the only real cpu work that will do the process for the brutforce part*/

void prepare_command_builder(char *command, char **prompts) {
  /*Gather all the templates, assign handlers, prepare the fix part, also check if session allready exist to continue it unstead of creating new one*/
  size_t command_size;
  command_builder_argv = arg_vector_from_string(command, &command_size);
  Placeholder **placeholders = (Placeholder **)create_vector(0);

  // Getting every placeholders

  char *sub_part;
  size_t it = 0;
  while (sub_part = command_builder_argv[it++]) {
    Placeholder **new_placeholders = placeholder_parse_string(sub_part, '{', '}', '\\');
    unit_num = concatenate_vector((void ***)&placeholders, (void **)new_placeholders);
  }

  // Setting the switching units
  templates = malloc(sizeof(Template_unit) * unit_num);
  for (size_t i = 0; i < unit_num; i++) {
    templates[i].placeholder = placeholders[i];
    templates[i].handler = handler_new(*placeholders[i]->base_string + placeholders[i]->begin + 1, placeholders[i]->size_place - 1);
  }
}

// TODO do a sneaky cartesian product along with furtivity option (change order to have change in each consecutive template
bool command_builder_next_command() { // Cartesian product
  Template_unit *current_template = templates;
  char *next_value = handler_next(current_template->handler);
  while (!next_value) { // the handler boucled once
    current_template++;
    if (current_template - templates > unit_num) // everything had been done
      return true;
    next_value = handler_next(current_template->handler);
  }
  placeholder_switch(current_template->placeholder, next_value);
  iterator++;
  return false;
}

void command_builder_fix(size_t positions, char *fix);

char *command_builder_serialize();
/*Serialize the state*/

void *command_builder_unserialize(char *string);
/*Set the state as specified in string*/
