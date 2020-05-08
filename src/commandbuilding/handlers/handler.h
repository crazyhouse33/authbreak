//managing broken include
#ifndef XXX_HANDLER_GUARD_XXX
#define XXX_HANDLER_GUARD_XXX
#include <stddef.h>//size_t

typedef enum Handler_type{handler_file, handler_iterator} Handler_type;
typedef struct Handler
{
	char* main_component;
	int (*getValues)();// Full the buffer, the buffer act as a cache 
	unsigned long int pos;//position of the handler
	char** buffer;//In memory guesses


} Handler;

Handler* handler_new(char* template_string);
/*Handler constructor, create a pointer pointing to the handler initialized by the string*/

void handler_init(Handler* emptypointer, char* template_string, size_t until, size_t buffer_size);
/*Initialize memory pointed by emptypointer to the template_string setup. Consider the string end after until bytes, set the buffer to a certain size*/

char* handler_next(Handler* handler);
/*Return next value for the template and increment pos*/

void handler_set(Handler* handler, unsigned long int n);
/*Set pos to n */

#define handler_reset(handler) handler_set(handler, 0)
#endif
