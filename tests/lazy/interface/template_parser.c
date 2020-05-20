#include "template_parser.h"
#include "default_options.h"
#include "handler.h"
#include "munit.h"

Handler *handler_parse_generate(char *template_string, size_t until) {
  Handler *handler = malloc(sizeof(Handler));
  parse_injection_template(handler, template_string, until);
  return handler;
}

// TODO other platforms paths
#define TEST_PATH strdup("/usr/include/stdio.h")
#define TEST_PATH_AMBIGIOUS "8:15"

int main() {
  DEFAULT_CHARSET = "abcdefghijklmnopqrstuvwxyz0123456789";
  DEFAULT_LEN_MIN = 0;
  DEFAULT_LEN_MAX = 8;
  DEFAULT_SEPARATOR = '\n';

  char *template_string = strdup("");
  size_t size = strlen(template_string);
  Handler *handler = handler_parse_generate(template_string, size);

  munit_assert_int(handler->type, ==, iterator);
  munit_assert_string_equal(handler->options.charset, DEFAULT_CHARSET);
  munit_assert_int(handler->options.len_min, ==, DEFAULT_LEN_MIN);
  munit_assert_int(handler->options.len_max, ==, DEFAULT_LEN_MAX);

  template_string = strdup(":");
  size = strlen(template_string);
  handler = handler_parse_generate(template_string, size);
  munit_assert_int(handler->type, ==, iterator);
  munit_assert_string_equal(handler->options.charset, DEFAULT_CHARSET);
  munit_assert_int(handler->options.len_min, ==, DEFAULT_LEN_MIN);
  munit_assert_int(handler->options.len_max, ==, DEFAULT_LEN_MAX);

  template_string = strdup(",charset=abc");
  size = strlen(template_string);
  handler = handler_parse_generate(template_string, size);

  munit_assert_int(handler->type, ==, iterator);
  munit_assert_string_equal(handler->options.charset, "abc");
  munit_assert_int(handler->options.len_min, ==, DEFAULT_LEN_MIN);
  munit_assert_int(handler->options.len_max, ==, DEFAULT_LEN_MAX);

  template_string = strdup("  0  : 54  ,charset=abc");
  size = strlen(template_string);
  handler = handler_parse_generate(template_string, size);

  munit_assert_int(handler->type, ==, iterator);
  munit_assert_string_equal(handler->options.charset, strdup("abc"));

  munit_assert_int(handler->type, ==, iterator);
  munit_assert_int(handler->options.len_min, ==, 0);
  munit_assert_int(handler->options.len_max, ==, 54);

  template_string = strdup(" :54,charset=abc");
  size = strlen(template_string);
  handler = handler_parse_generate(template_string, size);

  munit_assert_int(handler->type, ==, iterator);
  munit_assert_string_equal(handler->options.charset, "abc");

  munit_assert_int(handler->type, ==, iterator);
  munit_assert_int(handler->options.len_min, ==, DEFAULT_LEN_MIN);
  munit_assert_int(handler->options.len_max, ==, 54);

  template_string = strdup(" 15 :  ,charset=abc");
  size = strlen(template_string);
  handler = handler_parse_generate(template_string, size);

  munit_assert_int(handler->type, ==, iterator);
  munit_assert_string_equal(handler->options.charset, "abc");

  munit_assert_int(handler->type, ==, iterator);
  munit_assert_int(handler->options.len_min, ==, 15);
  munit_assert_int(handler->options.len_max, ==, DEFAULT_LEN_MAX);

  template_string = strdup("14 : 20");
  size = strlen(template_string);
  handler = handler_parse_generate(template_string, size);

  munit_assert_int(handler->type, ==, iterator);
  munit_assert_string_equal(handler->options.charset, DEFAULT_CHARSET);

  munit_assert_int(handler->type, ==, iterator);
  munit_assert_int(handler->options.len_min, ==, 14);
  munit_assert_int(handler->options.len_max, ==, 20);

  template_string = strdup("20");
  size = strlen(template_string);
  handler = handler_parse_generate(template_string, size);

  munit_assert_int(handler->type, ==, iterator);
  munit_assert_string_equal(handler->options.charset, DEFAULT_CHARSET);

  munit_assert_int(handler->type, ==, iterator);
  munit_assert_int(handler->options.len_min, ==, DEFAULT_LEN_MIN);
  munit_assert_int(handler->options.len_max, ==, 20);

  template_string = strdup(" , charset =  abc");
  size = strlen(template_string);
  handler = handler_parse_generate(template_string, size);

  munit_assert_int(handler->type, ==, iterator);
  munit_assert_string_equal(handler->options.charset, "abc");

  template_string = strdup(" , char =  abc");
  size = strlen(template_string);
  handler = handler_parse_generate(template_string, size);

  munit_assert_int(handler->type, ==, iterator);
  munit_assert_string_equal(handler->options.charset, "abc");

  template_string = TEST_PATH;
  size = strlen(template_string);
  handler = handler_parse_generate(template_string, size);

  munit_assert_int(handler->type, ==, file);
  munit_assert_int(handler->options.separator, ==, DEFAULT_SEPARATOR);

  template_string = strdup(TEST_PATH_AMBIGIOUS ", charset =  abc, type=iterator");
  size = strlen(template_string);
  handler = handler_parse_generate(template_string, size);

  munit_assert_int(handler->type, ==, iterator);
  munit_assert_string_equal(handler->options.charset, "abc");

  return 0;
}
