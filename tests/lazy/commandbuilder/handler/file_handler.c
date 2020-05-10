#include "file_handler.h"
#include "handler.h"
#include "handler_test.h"
#include "munit.h"
#include <string.h>

#define test_file strdup("GITINCLUDEguess.list")

void test_newline() {
  Handler *handler = malloc(sizeof(Handler));
  handler->main_component = test_file;
  handler->options = (Handler_options){.separator = '\n', .charset = NULL, .len_min = 0, .len_max = 0};
  file_handler_init_special_needs(handler);
  char *res = file_handler_get_current(handler);
  munit_assert_string_equal(res, "GUESS1;");

  res = file_handler_next(handler);
  munit_assert_string_equal(res, "GUESS2;");

  res = file_handler_next(handler);
  munit_assert_string_equal(res, "GUESS3;");

  res = file_handler_next(handler);
  munit_assert_ptr(res, ==, NULL);

  res = file_handler_next(handler);
  munit_assert_string_equal(res, "GUESS1;");
}

void test_colon() {
  Handler *handler = malloc(sizeof(Handler));
  handler->main_component = test_file;
  handler->options = (Handler_options){.separator = ';', .charset = NULL, .len_min = 0, .len_max = 0};
  file_handler_init_special_needs(handler);
  char *res = file_handler_get_current(handler);
  munit_assert_string_equal(res, "GUESS1");

  res = file_handler_next(handler);
  munit_assert_string_equal(res, "\nGUESS2");

  res = file_handler_next(handler);
  munit_assert_string_equal(res, "\nGUESS3");

  res = file_handler_next(handler);
  munit_assert_ptr(res, ==, NULL);

  res = file_handler_next(handler);
  munit_assert_string_equal(res, "GUESS1");
}

void generic_test() {
  Handler *handler = malloc(sizeof(Handler));
  handler->main_component = test_file;
  handler->options = (Handler_options){.separator = ';', .charset = NULL, .len_min = 0, .len_max = 0};
  file_handler_init_special_needs(handler);

  Handler *fake_handler = malloc(sizeof(Handler));
  fake_handler->main_component = test_file;
  fake_handler->options = (Handler_options){.separator = ';', .charset = NULL, .len_min = 0, .len_max = 0};
  file_handler_init_special_needs(fake_handler);
  assert_handler_generic_iteration_test(handler, fake_handler, 3);
}

int main() {
  test_colon();
  test_newline();
  generic_test();

  return 0;
}
