#include "template_parser.h"
#include "error.h"
#include "handler_front.h"
#include "trim_string.h" //trim
#include <stdbool.h>
#include <stdlib.h> //malloc

static bool guess_main_component(Handler *handler, char *string_begin, size_t until) {
  size_t number_of_enum = get_Handler_type_number();
  Handler_type *types = get_Handler_type_iterator();
  // Calling every type parsing
  for (size_t i = 0; i < number_of_enum; i++) {
    if (handler_parse_main_component(handler, types[i], string_begin, until)) {
      return true;
    }
  }
  return false;
}

static bool select_type(Handler *handler, char *template_string, size_t until) {
  /*Set the good type for handler, look for type option first, then use automatic selection. This is necessary because the parsing of the options is different according to the type, so to branch to
   * the right function we need to determine it first*/

  // first option is interpreted as main component, we save it for later
  char *option_block_end = memchr(template_string, ',', until);
  if (option_block_end == NULL) { // allready last, dont parse more
    option_block_end = template_string + until++;
  }

  until -= option_block_end - template_string + 1;

  char *first_end = option_block_end;
  char *first_begin = template_string;

  template_string = option_block_end + 1;

  // the rest are options
  while (until > 0) {
    option_block_end = memchr(template_string, ',', until);
    if (!option_block_end)
      option_block_end = template_string + until++; // until++ because we are removing an inexistant separator for the last

    until -= option_block_end - template_string + 1;

    char *key;
    char *value;
    size_t value_size;
    size_t key_size;

    handler_separate_option(template_string, option_block_end - template_string, &key, &value, &key_size, &value_size);

    // looking for type=...

    Authorized_file_option_key key_type;
    if (str_to_Authorized_file_option_key(key, key_size, &key_type)) // the type is parsable among the options and had been set up
      if (key_type == type) {
        handler->type = str_to_Handler_type_no_fail(value, value_size);
        return false;
      }
    template_string = option_block_end + 1;
  }

  if (!guess_main_component(handler, first_begin, first_end - first_begin))
    controlled_error_msg(2, "Parsing Error: Type of template \"%.*s\n...\" could not be automatically determined. Check the validity of the inputs or use the type option.",
                         option_block_end - first_begin, first_begin);
  return true;
}

void parse_injection_template(Handler *handler, char *template_string, size_t until) {
  handler_set_default(handler);
  bool need_to_parse_main = !select_type(handler, template_string, until);
  char *option_block_end = memchr(template_string, ',', until);
  if (!option_block_end)
    option_block_end = template_string + until++;

  if (need_to_parse_main)
    handler_parse_main_component(handler, handler->type, template_string, option_block_end - template_string); // we parse main with the good type
  until -= option_block_end - template_string + 1;
  template_string = option_block_end + 1;

  // the rest are options
  while (until > 0) {
    option_block_end = memchr(template_string, ',', until);
    if (!option_block_end)
      option_block_end = template_string + until++; // until++ because we are removing an inexistant separator for the last
    until -= option_block_end - template_string + 1;
    handler_parse_option(handler, template_string, option_block_end - template_string);
    template_string = option_block_end + 1;
  }
}
