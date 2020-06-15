#include "stdbool.h"
#include <stddef.h> //size_t
//This module iterate on the possibilities created by the user placement of injection point. For performance reason we reflect changes of state unstead of allocating memory to return a prompt and argv.

extern char** command_builder_argv; // any call to defined functions are reflected on this 2 variables
extern char** command_builder_prompt; 


void prepare_command_builder (char* command, char** prompts);
/*Gather all the templates, assign handlers, prepare the fix parts*/

bool command_builder_next_command();
/*set argv and prompt to next combinaison and return boolean indicating if the builder iterated on everything yet*/

char* command_builder_current_command();
/*Get a string representing what is the current command and prompt according to all the the handlers*/

void command_builder_fix(size_t positions, char* fix);
/* Permanently replace a handler by a fix string*/


char* command_builder_serialize();
/*Serialize the state*/

void* command_builder_unserialize(char* string);
/*Set the state as specified in string*/


