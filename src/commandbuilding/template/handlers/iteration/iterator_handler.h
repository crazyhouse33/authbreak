#include "handler.h"         //Handler


typedef struct Iterator_needs
{
	char* current;//current string
	char* charset_next_table;//table memorizing next char for each char
	size_t charset_len;
	size_t len;//actual len of string

} Iterator_needs;



char* iterator_handler_next(Handler* handler);
/*Next guess is incrementation of current stuff in a cartesian product way on the given charset*/

void iterator_handler_init_special_needs(Handler* handler);
//Initialize iteration, create permutation

void iterator_handler_reset_to(Handler* handler, size_t pos);
//Reset handler to given position


void iterator_handler_reset(Handler* handler);
//Reset handler to 0 (faster)

void iterator_handler_free_needs(Handler* handler);

size_t iterator_handler_size(Handler* handler);
 //get number of element in handler


