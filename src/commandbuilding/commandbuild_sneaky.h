#include <stdbool.h>
#include <stddef.h> //size_t
#include "template.h"
#include "commandbuild.h"

typedef struct Sneaky_command_builder {
	Command_builder builder;
	size_t* ghost_sizes;
	size_t* sizes;
	size_t* pos; // this is just a buffer for the fix function
} Sneaky_command_builder;

Sneaky_command_builder* sneaky_command_builder_new (char* command, char** prompts);
/*Gather all the templates, append newline to prompts*/

bool sneaky_command_builder_next_command(Sneaky_command_builder* builder);
/*Set argv and prompt to next combinaison and return true if done */

char *sneaky_command_builder_current_command(Sneaky_command_builder* builder);

Sneaky_command_builder* command_builder_sneakify( Command_builder* builder);
// wrap a build into a sneaky one


