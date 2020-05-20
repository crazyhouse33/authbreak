#include "search_string.h"
#include "munit.h"
#include <sys/types.h>
void test_first_diff(char *s1, char *s2, size_t s, size_t expected) {
  size_t res = first_diff(s1, s2, s);
  munit_assert_size(res, ==, expected);
}

void test_get_unique() {
  char *list[] = {"separator", "septre", "cylynder", "star", NULL};
  ssize_t res = get_unique_matching_string(list, "sep", 3);
  munit_assert_int(res, ==, SEARCH_ERROR_MATCHS_AMBIGUITY);

  res = get_unique_matching_string(list, "s", 1);
  munit_assert_int(res, ==, SEARCH_ERROR_MATCHS_AMBIGUITY);

  res = get_unique_matching_string(list, "t", 1);
  munit_assert_int(res, ==, SEARCH_ERROR_NO_MATCH);

  res = get_unique_matching_string(list, "separatora", 10);
  munit_assert_int(res, ==, SEARCH_ERROR_NO_MATCH);

  res = get_unique_matching_string(list, "separatora", 9);
  munit_assert_int(res, ==, 0);

  res = get_unique_matching_string(list, "c", 1);
  munit_assert_int(res, ==, 2);

  res = get_unique_matching_string(list, "star", 4);
  munit_assert_int(res, ==, 3);
}

int main() {
  test_first_diff("tata", "toto", 4, 1);
  test_first_diff("toto", "toto", 4, 4);
  test_first_diff("toto", "toto", 5, 5);
  test_first_diff("toto", "to", 2, 2);
  test_first_diff("abs", "obs", 3, 0);
  test_first_diff("tas", "tat", 3, 2);

  test_get_unique();
  return 0;
}
