#include "handler_front.h"
#include "default_options.h" //default parsing stuff
#include "error.h"           //controlled_error
#include "file_info.h"       //is_openable
#include "handler.h"         // include handlers options defined by the backend
#include "trim_string.h"     //simplify user syntax
#include <stdlib.h>          //str_tol

// Specifying error msg for options key errors

#define ERROR_STR_OPT_NO_MATCH(X) "Option key \"%s\" is not valid for a " #X ", chose among the following valid options:\n%s\n"
#define ERROR_STR_OPT_AMBIGIOUS(X) "Option key %s is ambigious for a " #X ", choose among the valids options:\n%s\n"

DEFINE_ENUM(Authorized_file_option_key, ERROR_STR_OPT_NO_MATCH(file template), ERROR_STR_OPT_AMBIGIOUS(file template), AUTHORIZED_FILE);

DEFINE_ENUM(Authorized_iterator_option_key, ERROR_STR_OPT_NO_MATCH(iterator template), ERROR_STR_OPT_AMBIGIOUS(iterator template), AUTHORIZED_ITERATOR);

char handler_parse_separator(char *separator, size_t until) {
  if (until != 1) {
    controlled_error_msg(2, "Parsing Error: Separator \"%s\" contain more than one character", separator);
  }
  return *separator;
}

static void handler_parse_type(Handler *handler, char *type, size_t until) {
  Handler_type res;
  handler->type = str_to_Handler_type_no_fail(type, until);
}

static char *unify_charset(char *charset, size_t until) { return strndup(charset, until); }

void handler_parse_charset(Handler *handler, char *charset, size_t until) { handler->options.charset = unify_charset(charset, until); }

static bool file_handler_parse_main_component(Handler *handler, char *main, size_t until) {

  if (!is_openable_file_until(main, until))
    return false;
  handler->type = file;
  handler->main_component = strndup(main, until);
  return true;
}

#define USE_THE_DEFAULTw -1
#define INVALID_FORMATw -2
#define NOT_IN_RANGE_INTw -3
static long int handler_parse_len(char *begin, size_t until) {

  if (left_trim(begin) >= begin + until) // empty stuff
    return USE_THE_DEFAULTw;

  char *end;
  long int res = strtol(begin, &end, 0);
  left_trim_in_place(&end); // we ignore the spaces

  if (res < 0 || res > 65535)
    return NOT_IN_RANGE_INTw;
  else if (end >= begin + until) // is a number + spaces
    return res;
  else
    return INVALID_FORMATw;
}

// TODO read from cli arg
static bool attribute_len(long int len, unsigned short *placeholder, unsigned short default_len) {
  /*Write len at placeholder or manage error if needed*/
  switch (len) {
  case USE_THE_DEFAULTw:
    *placeholder = default_len;
    return true;
    break;
  case NOT_IN_RANGE_INTw:
    // TODO LOG controlled_error_msg(2,"PARSING ERROR: %d Is an invalid lengh for iterator template. Choose an integer between 0 and 65535", res);
    return false;
    break;
  case INVALID_FORMATw:
    // TODO LOG controlled_error_msg(2, "PARSING ERROR: Invalid [0, 65535] integer around %s", main);
    return false;

  default:
    *placeholder = (unsigned short)len;
    return true;
  }
}

// TODO DO a proper logging system that would explain choice about handlers
static bool iterator_handler_parse_main_component(Handler *handler, char *main, size_t until) {
  char *colon;
  if (!(colon = memchr(main, ':', until))) { // No separation
    long int len = handler_parse_len(main, until);
    if (attribute_len(len, &handler->options.len_max, DEFAULT_LEN_MAX)) {
      handler->type = iterator;
      return true;
    }
    return false;
  }

  size_t until1 = colon - main;
  size_t until2 = until - until1 - 1;

  long int len1 = handler_parse_len(main, until1);

  if (!attribute_len(len1, &handler->options.len_min, DEFAULT_LEN_MIN))
    return false;

  long int len2 = handler_parse_len(colon + 1, until2);
  if (attribute_len(len2, &handler->options.len_max, DEFAULT_LEN_MAX)) {
    handler->type = iterator;
    return true;
  }
  return false;
}

bool handler_parse_main_component(Handler *handler, Handler_type type, char *main, size_t until) {

  // trimming stuff
  char *trimed_end = main + until;
  trim_point(&main, &trimed_end);
  until = trimed_end - main;

  switch (type) {
  case file:
    return file_handler_parse_main_component(handler, main, until);
  case iterator:
    return iterator_handler_parse_main_component(handler, main, until);
  }
}

static void handler_parse_option_value(Handler *handler, int option_type, char *opt_value_begin, size_t until) {

  switch (option_type) {
  case separator:
    handler->options.separator = handler_parse_separator(opt_value_begin, until);
    break;

  case charset:
    handler_parse_charset(handler, opt_value_begin, until);
    break;
  }
}

void handler_separate_option(char *option, size_t until, char **key, char **value, size_t *key_size, size_t *value_size) {
  /*Trim and separate key and values*/
  *key = left_trim(option);

  *value = get_after_sep_part(option, '=', until);
  char *key_end = get_pointer_to_last_white(option, (*value) - 1);
  left_trim_in_place(value);

  *value_size = option + until - *value;
  *key_size = key_end - *key;
}

#define CASE_FILTER_OPTIONS(X)                                                                                                                                                                         \
  case X:                                                                                                                                                                                              \
    option_key = str_to_Authorized_##X##_option_key_no_fail(key, key_size);                                                                                                                            \
    break

void handler_parse_option(Handler *handler, char *string_begin, size_t until) {
  /* Separate key and value, check if key is undersood option, feed handler the value
   * Notice than we dont trim value, because it may be desirable to acces some space, for exemple, for the separator
   * */
  char *value;
  char *key;

  size_t value_size;
  size_t key_size;

  handler_separate_option(string_begin, until, &key, &value, &key_size, &value_size);

  int option_key;
  switch (handler->type) {
    CASE_FILTER_OPTIONS(file);
    CASE_FILTER_OPTIONS(iterator);
  }

  handler_parse_option_value(handler, option_key, value, value_size);
}

// Its okay to have lazy same default initialiation for everyone, the front code is allready complex enought
void handler_set_default(Handler *handler) {
  handler->options.charset = DEFAULT_CHARSET;
  handler->options.len_min = DEFAULT_LEN_MIN;
  handler->options.len_max = DEFAULT_LEN_MAX;
  handler->options.separator = DEFAULT_SEPARATOR;
}
