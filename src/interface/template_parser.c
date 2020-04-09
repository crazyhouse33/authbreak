#include "template_parser.h"
#include "stringmy.h" //trim
#include <stdlib.h> //malloc

size_t parse_one_option(char* string_begin, char* string_end, Handler* handler){
	/* Set the handler option as the string read betwen the pointers say
	 * Expect pointer on begining and comma respectively
	 * */
	trim(string_begin, string_end);
	if (strcmp(string_begin, "B1") == 0) 
	{
		// do something
	} 
	else if (strcmp(string_begin, "xxx") == 0)
	{
		// do something else
	}
	/* more else if clauses */
	else /* default: */
	{
	}


};

/* We do it the most efficient way. No memory allocation, pointer playing
 * We iterate to the options blocks (separator is ,) 
 * */

Handler* parse_injection_template(char* template_string, size_t until){
	Handler* handler = malloc(sizeof(Handler));

	char* option_block_end;
	
	while ((option_block_end= memchr(template_string, ',', until)) != NULL){
		parse_one_option(template_string, option_block_end, handler );
		template_string=option_block_end;
		
	}

}




