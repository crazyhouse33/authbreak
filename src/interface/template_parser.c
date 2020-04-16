#include "template_parser.h"
#include "trim_string.h" //trim
#include <stdlib.h> //malloc

size_t parse_one_option(char* string_begin, Handler* handler){
	/* Set the handler option as the string read at string_begin
	 * option is in form key=value or just key.
	 * */
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

/* We do it the most efficient way. No memory allocation, just pointer playing
 * We iterate to the options blocks (separator is ,) 
 * */

Handler* parse_injection_template(char* template_string, size_t until){
	Handler* handler = malloc(sizeof(Handler));

	char* option_block_end;
	
	while ((option_block_end= memchr(template_string, ',', until)) != NULL){
		trim_in_place_preserve_right(&template_string, option_block_end);
		parse_one_option(template_string, handler );
		template_string=option_block_end;
		
	}

}




