#include "concat_string.h"
#include "munit.h"
#include <string.h>

void base() {
  char *test = strdup("tata");
  char *test2 = strdup("toto");
  char *res = get_concatenation_string_fast(test, test2, strlen(test), strlen(test2));

  munit_assert_string_equal(res, "tatatoto");
  munit_assert_ptr(test, !=, res);

  size_t size = concat_string_fast(&test, test2, strlen(test), strlen(test2));
  munit_assert_string_equal(test, "tatatoto");

  concat_string_fast_left(&test, "tonton", size);
  munit_assert_string_equal(test, "tatatototonton");
}

void others() {
  char a = 'a';
  char *test = strdup("tata");
  size_t size = concat_char(&test, a);
  munit_assert_string_equal(test, "tataa");
  munit_assert_size(size, ==, 5);

  char *test2 = strdup("toto");
  // TODO this should be before char
  size_t res = concat_string_cut(&test, test2, 2);
  munit_assert_string_equal(test, "tataato");
  munit_assert_size(size, ==, 5);
}

int main() {
  base();
  char *test = strdup("tata");
  char *test2 = strdup("toto");
  char *other = get_concatenation_string(test, test2);

  munit_assert_string_equal(other, "tatatoto");
  munit_assert_string_equal(test, "tata");
  munit_assert_ptr(test, !=, other);

  /*C dont allow that (realloc on literal)*/
  size_t size = concat_string(&test, test2);

  munit_assert_string_equal(test, "tatatoto");
  munit_assert_size(size, ==, strlen(test));

  others();
}
