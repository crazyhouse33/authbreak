#include <stddef.h>//size_t
typedef struct Handler
{
	char* main_component;
	int (*getValues)();// Full the buffer, the buffer act as a cache 
	size_t _buffer_size;
	unsigned long int pos;//position of the handler

} Handler;

Handler* handler_new(char* template_string);
/*Handler constructor, create a pointer pointing to the handler initialized by the string*/

void handler_init(Handler* emptypointer, char* template_string);
/*Initialize memory pointed by emptypointer to the template_string setup.*/

char* handler_next(Handler* handler);
/*Return next value for the template and increment pos*/

void handler_set(Handler* handler, unsigned long int n);
/*Set pos to n */

#define handler_reset(handler) handler_set(handler, 0)
