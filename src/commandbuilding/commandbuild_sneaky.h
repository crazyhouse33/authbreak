#include <stdbool.h>
#include <stddef.h> //size_t
#include "template.h"
#include "commandbuild.h"

typedef struct Sneaky_command_builder {
	Command_builder builder;
	size_t* ghost_sizes;
	size_t* sizes;
} Sneaky_command_builder;

Sneaky_command_builder* sneaky_command_builder_new (char* command, char** prompts);
/*Gather all the templates, append newline to prompts*/

bool sneaky_builder_next_command(Command_builder* builder);
/*Set argv and prompt to next combinaison and return true if done */

