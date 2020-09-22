#include "handler.h"
#include "handler_front.h"
#include "munit.h"

Handler *handler_parse_main_generate(Handler_type type, char *main, size_t until, bool *worked) {
  Handler *handler = malloc(sizeof(Handler));
  *worked = handler_parse_main_component(handler, type, main, until);
  return handler;
}

Handler *handler_parse_option_generate(Handler_type type, char *main, size_t until) {
  Handler *handler = malloc(sizeof(Handler));
  handler->type=type;
  handler_parse_option(handler, main, until);
  return handler;
}

void test_opt() {

  char *option;
  size_t size;
  Handler *res;

  option = strdup("charset=ab");
  size = strlen(option);
  res = handler_parse_option_generate(file, option, size);
  munit_assert_string_equal(res->options.charset, "ab");

  option = strdup("sep= ;");
  size = strlen(option);
  res = handler_parse_option_generate(file, option, size);
  munit_assert_int(res->options.separator, ==, ';');
}

void test_main_compo() {
  char *main_comp = strdup("3:4");
  size_t size = strlen(main_comp);
  bool worked;
  Handler *res = handler_parse_main_generate(file, main_comp, size, &worked);
  munit_assert_false(worked);

  res = handler_parse_main_generate(iterator, main_comp, size, &worked);
  munit_assert_true(worked);
  munit_assert_int(res->options.len_min, ==, 3);

  main_comp = strdup("/tmp/NONexist-fileuwxd");
  size = strlen(main_comp);
  res = handler_parse_main_generate(file, main_comp, size, &worked);
  munit_assert_false(worked);

  res = handler_parse_main_generate(iterator, main_comp, size, &worked);
  munit_assert_false(worked);
}

void test_option_bloc(char *bloc, char *expected_key, char *expected_value, size_t expected_key_size, size_t expected_value_size) {
  char *value;
  char *key;
  size_t value_size;
  size_t key_size;
  handler_separate_option(bloc, strlen(bloc), &key, &value, &key_size, &value_size);

  munit_assert_int(strncmp(key, expected_key, key_size), ==, 0);
  munit_assert_int(strncmp(value, expected_value, value_size), ==, 0);
  munit_assert_size(key_size, ==, expected_key_size);
  munit_assert_size(value_size, ==, expected_value_size);
}

int main() {
  test_opt();
  test_main_compo();
  test_option_bloc("k=t", "k", "t", 1, 1);
  test_option_bloc("   k=t ", "k", "t ", 1, 2);
  test_option_bloc("   k=    t ", "k", "t ", 1, 2);
  test_option_bloc("  k   =    t ", "k", "t ", 1, 2);
  test_option_bloc("  tonpere_le   =    boucher ", "tonpere_le", "boucher ", strlen("tonpere_le"), strlen("boucher "));
  return 0;
}
