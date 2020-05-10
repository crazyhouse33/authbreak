//managing broken include
#ifndef XXX_HANDLER_GUARD_XXX
#define XXX_HANDLER_GUARD_XXX
#include <stddef.h>//size_t

/*This functions declare the back end of handlers, for how the structures are properly set up check the interface/parse_template*/

typedef struct Handler_options{
	char separator;//Used for file for exemple, delimiter of guesses: file
	char* charset;//Used by iterator to know whith wich char he is playing: iterator
	unsigned short len_min;//Used by iterator to start at specified len: iterator
	unsigned short len_max;//Used by iterator to stop at specified len: iterator



} Handler_options;

typedef enum Handler_type{file_handler, iterator_handler} Handler_type;//THE ORDER CORRESPOND TO THE PARSING PRIORITY
typedef struct Handler
{
	Handler_type type;
	char* main_component;
	Handler_options options;
	void* special_needs;//Here go, for exemple, the file pointer of the file handler
} Handler;

Handler* handler_new(char* template_string, size_t until);
/*Handler constructor, create a pointer pointing to the handler initialized by the string*/

void handler_init(Handler* emptypointer, char* template_string, size_t until);
/*Initialize memory pointed by emptypointer to the template_string setup. Consider the string end after until bytes*/

char* handler_next(Handler* handler);
/*Return next value for the template. If we reach end of iterations, return NULL and reset the handler to the begining*/

char* handler_get_current(Handler* handler);//This is unavoidable for the first value
/*Return current value of the handler*/

void handler_free(Handler* handler);
/*Free the handler*/

#endif
