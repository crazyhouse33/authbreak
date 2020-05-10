#include "template_parser.h"
#include "error.h"
#include "trim_string.h" //trim
#include <stdlib.h>      //malloc
#include <stdbool.h>

static bool parse_one_option(Handler *handler, char *string_begin, char *string_end) {
  /* Set the handler option as the string read at string_begin
   * option is in form key=value or just key.
   * */
  size_t until = string_end - string_begin;
  char *after_equal = get_after_sep_part(string_begin, '=', until);
  size_t after_equal_until = string_begin + until - after_equal;
  if (strncmp(string_begin, "type", until) == 0) {
    handler->type = str_to_Handler_type(after_equal, after_equal_until);
    return true;

    // do something
  } else if (strncmp(string_begin, "xxx", until) == 0) {
    // do something else
  }
  /* more else if clauses */
  else /* default: */
  {
  }
}

static void parse_main_component(Handler *handler, char *string_begin, char *string_end) {
  // manage type of handler according to the main component

  // early stop if allready set
  if (handler->type ! = invalid_handler)
    return

        Handler_type type;
  for (type = file_handler; type < iterator_handler; type++) {
    if (handler_parse_main(handler, type))
      return;
  }

  void parse_injection_template(Handler * handler, char *template_string, size_t until) {

    // first option is interpreted as main component, we save it for later
    char *option_block_end = memchr(template_string, ',', until);
    trim_in_place_preserve_right(&template_string, option_block_end);
    char *first_end = option_block_end;
    char *first_begin = template_string;

    until -= option_block_end - template_string + 1;
    template_string = option_block_end + 1;

    bool type_is_knowned = false;
    // the rest are options
    while (option_block_end = memchr(template_string, ',', until)) {
      trim_in_place_preserve_right(&template_string, option_block_end);
      type_is_knowned = parse_one_option(handler, template_string, option_block_end);
      until -= option_block_end - template_string + 1;
      template_string = option_block_end + 1;
    }

    if (!type_is_knowned)
      parse_main_component(handler, first_begin, first_end);
  }
