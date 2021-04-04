#include "handler.h"         //Handler


typedef struct Iterator_needs
{
	char* current;//current string
	char* charset_next_table;//table memorizing next char for each char
	size_t len;//actual len of string

	//memory gestion
	size_t real_size;
} Iterator_needs;



char* iterator_handler_next(Handler* handler);
/*Next guess is incrementation of current stuff in a cartesian product way on the given charset*/

void iterator_handler_init_special_needs(Handler* handler);
//Initialize iteration, create permutation


char* iterator_handler_get_current(Handler* handler);
//return current


void iterator_handler_free_needs(Handler* handler);

