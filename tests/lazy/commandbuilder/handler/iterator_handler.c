#include "iterator_handler.h"
#include "handler.h"
#include "handler_test.h"
#include "math.h"
#include "munit.h"
#include <string.h> //strdup

void test_iteration(char *CHARSET, ssize_t LEN_MIN, ssize_t LEN_MAX) {
  size_t charset_size = strlen(CHARSET);
  Handler *handler = malloc(sizeof(Handler));
  handler->type = iterator;
  handler->main_component = strdup("");
  handler->options = (Handler_options){.charset = CHARSET, .len_min = LEN_MIN, .len_max = LEN_MAX};
  iterator_handler_init_special_needs(handler);

  size_t expected = 0;

  while (LEN_MAX >= LEN_MIN)
    expected += pow(charset_size, LEN_MAX--);

  Handler *fake_handler = malloc(sizeof(Handler));
  fake_handler->type = iterator;
  fake_handler->main_component = strdup("");
  fake_handler->options = (Handler_options){.charset = strdup(CHARSET), .len_min = LEN_MIN, .len_max = LEN_MAX};
  iterator_handler_init_special_needs(fake_handler);

  assert_handler_generic_iteration_test(handler, fake_handler, expected);
}

int main() {
  test_iteration("123", 0, 4);
  test_iteration("123", 2, 4);
  test_iteration("01", 0, 3);
  test_iteration("1", 0, 3);
  return 0;
}
