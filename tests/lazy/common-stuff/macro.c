#include "macro_util.h"
#include "munit.h"

int main() {
  munit_assert_int(5, ==, MACRO_N_ARG(hey, how, nop, ta, to));
  char *array[] = {TOKENIZE(toto, tata)};
  munit_assert_string_equal("toto", array[0]);
  munit_assert_string_equal("tata", array[1]);

  return 0;
}
