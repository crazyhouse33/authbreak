



typedef struct Payload
{
  char* commandLine;                
  char**  prompt[100];
} Payload;

void prepare_command_builder (char* command, char** prompts);
/*Gather all the templates, assign handlers, prepare the fix part, also check if session allready exist to continue it unstead of creating new one*/

Payload* command_builder_next_command();
/*return the next command and prompt combinaison*/

Payload* command_builder_next_command_fixed(int* positions, char** fix);
/*This function does the same as Command_builder_next_command but dont use the handlers for the given postion, where it use the the coresponding fix string unstead*/

void command_builder_fix(int* positions, char* fix);
/* Permanently replace the handler by a fix string*/


char* command_builder_serialize();
/*Serialize the state*/

void* command_builder_unserialize(char* string);
/*Set the state as specified in string*/


