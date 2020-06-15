#include "search_string.h"
#include "munit.h"
#include <stdbool.h>
#include <sys/types.h>
void test_common_part(char *s1, char *s2, size_t s, size_t expected) {
  size_t res = common_substring_size(s1, s2, s);
  munit_assert_size(res, ==, expected);
}
void test_get_unique2() { // help reproduce a bug I dont undertand
  char *list[] = {"out_eq", "time", NULL};
  ssize_t res = get_unique_matching_string(list, "output", 6);
  munit_assert_int(res, ==, SEARCH_ERROR_NO_MATCH);
}

void test_get_unique() {
  char *list[] = {"separator", "septre", "cylynder", "star", "septree", NULL};
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

  res = get_unique_matching_string(list, "septre", 6);
  munit_assert_int(res, ==, 1);

  char *list2[] = {"<", "<=", ">", ">=", "=", "==", NULL};
  char *valid;
  res = get_unique_matching_string_tolerant(list2, "<a", 2, &valid); // resistent to bullshit on the right
  munit_assert_int(res, ==, 0);
  munit_assert_int(*valid, ==, '<');

  res = get_unique_matching_string_tolerant(list2, "<=", 2, &valid);
  munit_assert_int(res, ==, 1);
  munit_assert_int(*valid, ==, '=');

  res = get_unique_matching_string_tolerant(list2, "<", 1, &valid);
  munit_assert_int(res, ==, 0);

  munit_assert_int(*valid, ==, '<');

  res = get_unique_matching_string_tolerant(list2, "<", 2, &valid);
  munit_assert_int(res, ==, 0);

  munit_assert_int(*valid, ==, '<');

  res = get_unique_matching_string_tolerant(list2, "==", 2, &valid);
  munit_assert_int(res, ==, 5);

  munit_assert_int(*valid, ==, '=');

  res = get_unique_matching_string_tolerant(list2, "==", 1, &valid);
  munit_assert_int(res, ==, 4);

  res = get_unique_matching_string_tolerant(list2, "=", 2, &valid);
  munit_assert_int(res, ==, 4);

  munit_assert_int(*valid, ==, '=');
}

int main() {
  test_common_part("tata", "toto", 4, 1);
  test_common_part("toto", "toto", 4, 4);
  test_common_part("toto", "toto", 5, 5);
  test_common_part("toto", "totoa", 5, 4);
  test_common_part("toto", "to", 2, 2);
  test_common_part("abs", "obs", 3, 0);
  test_common_part("tas", "tat", 3, 2);

  test_get_unique();
  test_get_unique2();
  return 0;
}
