#include "file_handler.h"
#include "handler.h"
#include "handler_test.h"
#include "munit.h"
#include <string.h>

// The unix convention that put \n at end of every file make the parsing harder than it should be. We test the ability to use edge case (empty strings) with newline or whatever as separator
#define test_file strdup("../test_data/list/guess.list")

void test_newline() {
  Handler *handler = malloc(sizeof(Handler));
  handler->main_component = test_file;
  handler->type = file;
  handler->options = (Handler_options){.separator = '\n', .charset = NULL, .len_min = 0, .len_max = 0};
  file_handler_init_special_needs(handler);
  char *res = file_handler_next(handler);
  munit_assert_string_equal(res, "GUESS1;");

  res = file_handler_next(handler);
  munit_assert_string_equal(res, "GUESS2;");

  res = file_handler_next(handler);
  munit_assert_string_equal(res, "GUESS3");

  res = file_handler_next(handler);
  munit_assert_ptr(res, ==, NULL);

  handler_reset(handler);
	res = file_handler_next(handler);
  munit_assert_string_equal(res, "GUESS1;");
}

void test_colon() {
  Handler *handler = malloc(sizeof(Handler));
  handler->type = file;

  handler->main_component = test_file;
  handler->options = (Handler_options){.separator = ';', .charset = NULL, .len_min = 0, .len_max = 0};
  file_handler_init_special_needs(handler);
  char *res = file_handler_next(handler);
  munit_assert_string_equal(res, "GUESS1");

  res = file_handler_next(handler);
  munit_assert_string_equal(res, "\nGUESS2");

  res = file_handler_next(handler);
  munit_assert_string_equal(res, "\nGUESS3");

  res = file_handler_next(handler);
  munit_assert_ptr(res, ==, NULL);

  handler_reset(handler);

  res = file_handler_next(handler);
  munit_assert_string_equal(res, "GUESS1");

  res = file_handler_next(handler);
  munit_assert_string_equal(res, "\nGUESS2");
}

void test_colon2() {
  Handler *handler = malloc(sizeof(Handler));
  handler->type = file;

  handler->main_component = "../test_data/list/guess2.list";
  handler->options = (Handler_options){.separator = ';', .charset = NULL, .len_min = 0, .len_max = 0};
  file_handler_init_special_needs(handler);
  char *res = file_handler_next(handler);
  munit_assert_string_equal(res, "GUESS1");

  res = file_handler_next(handler);
  munit_assert_string_equal(res, "\nGUESS2");

  res = file_handler_next(handler);
  munit_assert_string_equal(res, "\nGUESS3 \n hey\n");

  res = file_handler_next(handler);
  munit_assert_ptr(res, ==, NULL);

  handler_reset(handler);

  res = file_handler_next(handler);
  munit_assert_string_equal(res, "GUESS1");

  res = file_handler_next(handler);
  munit_assert_string_equal(res, "\nGUESS2");
}

void generic_test() {
  Handler *handler = malloc(sizeof(Handler));
  handler->main_component = test_file;
  handler->type = file;
  handler->options = (Handler_options){.separator = ';', .charset = NULL, .len_min = 0, .len_max = 0};
  file_handler_init_special_needs(handler);

  Handler *fake_handler = malloc(sizeof(Handler));
  fake_handler->main_component = test_file;
  fake_handler->type = file;
  fake_handler->options = (Handler_options){.separator = ';', .charset = NULL, .len_min = 0, .len_max = 0};
  file_handler_init_special_needs(fake_handler);
  assert_handler_generic_iteration_test(handler, fake_handler, 3);
}

void test_another_complex_file() {
  Handler *handler = malloc(sizeof(Handler));
  handler->type = file;

  handler->main_component = "../test_data/list/complex.list";
  handler->options = (Handler_options){.separator = ';', .charset = NULL, .len_min = 0, .len_max = 0};
  file_handler_init_special_needs(handler);
  char *res = file_handler_next(handler);
  munit_assert_string_equal(res, "");

  res = file_handler_next(handler);
  munit_assert_string_equal(res, "\nhey");

  res = file_handler_next(handler);
  munit_assert_string_equal(res, "ho");

  res = file_handler_next(handler);
  munit_assert_string_equal(res, "");

  res = file_handler_next(handler);
  munit_assert_ptr(res, ==, NULL);

  handler_reset(handler);

  res = file_handler_next(handler);
  munit_assert_string_equal(res, "");

  res = file_handler_next(handler);
  munit_assert_string_equal(res, "\nhey");

  res = file_handler_next(handler);
  munit_assert_string_equal(res, "ho");

  res = file_handler_next(handler);
  munit_assert_string_equal(res, "");
}

void test_another_complex_file_newline() {
  Handler *handler = malloc(sizeof(Handler));
  handler->type = file;
  handler->main_component = "../test_data/list/complex.list";
  handler->options = (Handler_options){.separator = '\n', .charset = NULL, .len_min = 0, .len_max = 0};
  file_handler_init_special_needs(handler);
  char *res = file_handler_next(handler);
  munit_assert_string_equal(res, ";");

  res = file_handler_next(handler);
  munit_assert_string_equal(res, "hey;ho;");

  res = file_handler_next(handler);
  munit_assert_ptr(res, ==, NULL);

  handler_reset(handler);

  res = file_handler_next(handler);
  munit_assert_string_equal(res, ";");

  res = file_handler_next(handler);
  munit_assert_string_equal(res, "hey;ho;");

  res = file_handler_next(handler);
  munit_assert_ptr(res, ==, NULL);

}
//TODO move to template test
void test_reset() {
/*
  Handler *handler = malloc(sizeof(Handler));
  handler->type = file;

  handler->main_component = "../test_data/list/complex.list";
  handler->options = (Handler_options){.separator = ';', .charset = NULL, .len_min = 0, .len_max = 0};
  file_handler_init_special_needs(handler);
  char* res;
  handler_reset_to(handler,3);
  res=file_handler_next(handler);
  munit_assert_string_equal(res, "");//3

  res = file_handler_next(handler);
  munit_assert_ptr(res, ==, NULL);

  
  handler_reset_to(handler,2);
  res=file_handler_next(handler);
  munit_assert_string_equal(res, "ho");//2

  handler_reset_to(handler,1);
  res=file_handler_next(handler);
  munit_assert_string_equal(res, "\nhey");//1

  res=file_handler_next(handler);
  munit_assert_string_equal(res, "ho");//2

  handler_reset_to(handler,0);
  res=file_handler_next(handler);
  munit_assert_string_equal(res, ""); //0

  res=file_handler_next(handler);
  munit_assert_string_equal(res, "\nhey");//1
*/
	return;
}


int main() {
  test_colon();
  test_colon2();
  test_newline();
  test_another_complex_file();
  test_another_complex_file_newline();
  generic_test();
  test_reset();

  return 0;
}
