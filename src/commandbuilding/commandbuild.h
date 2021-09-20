#include <stdbool.h>
#include <stddef.h> //size_t
#include "template.h"
//This module iterate on the possibilities created by the user placement of injection point. 
typedef struct Command_builder {
	   Template** templates;
	   char** argv;
	   char** prompts;
	   unsigned short templates_num;
	   unsigned short cartesian_it;//current temp getting inc
} Command_builder;


Command_builder* command_builder_new (char* command, char** prompts);
/*Gather all the templates, append newline to prompts*/

void command_builder_init(Command_builder* builder, char* command, char** prompts);
/*Gather all the templates, append newline to prompts*/


bool command_builder_next_command(Command_builder* builder);
/*Set argv and prompt to next combinaison and return true if done */

char* command_builder_current_command(Command_builder* builder);
/*Get a string representing what is the current command and prompt according to all the the handlers states*/

void command_builder_fix(Command_builder* builder, size_t positions, char* fix);
/* Permanently replace a handler by a fix string*/

char* command_builder_serialize(Command_builder* builder);
/*Serialize the state*/

void* command_builder_unserialize(Command_builder* builder,char* string);
/*Set the state as specified in string*/

size_t command_builder_size(Command_builder* builder);
/*Retrieve number of elements that contain a builder*/


