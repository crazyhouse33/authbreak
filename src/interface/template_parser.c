#include "template_parser.h"
#include "trim_string.h" //trim
#include <stdlib.h>      //malloc
#include "error.h"

static void parse_one_option( Handler *handler, char *string_begin, char* string_end) {
  /* Set the handler option as the string read at string_begin
   * option is in form key=value or just key.
   * */
size_t until = string_end - string_begin;
  if (strncmp(string_begin, "B1", until) == 0) {
    // do something
  } else if (strncmp(string_begin, "xxx", until) == 0) {
    // do something else
  }
  /* more else if clauses */
  else /* default: */
  {
  }

}


void parse_injection_template(Handler* handler, char *template_string, size_t until) {

	char *option_block_end;

	while (option_block_end = memchr(template_string, ',', until)) {
		trim_in_place_preserve_right(&template_string, option_block_end);
		parse_one_option(handler, template_string, option_block_end);
		until-= option_block_end - template_string +1 ;
		template_string = option_block_end+1;
	}
}
