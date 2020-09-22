#include "enum.h"
#include "munit.h"

char *no_match_format = "oups, y'a as de match";
char *ambigious_format = "oups, y'a trop de match";

#define NAME(XX)                                                                                                                                                                                       \
  XX(maman, "maman", )                                                                                                                                                                                 \
  XX(papa, "papa", )

DECLARE_ENUM(Parent, NAME);

DEFINE_ENUM(Parent, no_match_format, ambigious_format, NAME);

#define NAME2(XX)                                                                                                                                                                                      \
  XX(alfredo, "alfredo", )                                                                                                                                                                             \
  XX(alphonse, "alphonse", )                                                                                                                                                                           \
  XX(jacqueline, "jacqueline", = maman)

DECLARE_ENUM(Name, NAME2);

DEFINE_ENUM(Name, no_match_format, ambigious_format, NAME2);

int main() {
  Name result;
  bool valid = str_to_Name("alf", 3, &result);
  munit_assert_true(valid);

  munit_assert_int(result, ==, alfredo);

  Parent result_parent;
  valid = str_to_Parent("papa", 4, &result_parent);
  munit_assert_true(valid);
  munit_assert_int(result_parent, ==, papa);

  valid = str_to_Name("alp", 3, &result);
  munit_assert_true(valid);
  munit_assert_int(result, ==, alphonse);

  Parent result_invalid;
  valid = str_to_Parent("papaa", 5, &result_invalid);
  munit_assert_false(valid);

  valid = str_to_Parent("papa", 4, &result_parent);
  munit_assert_true(valid);
  munit_assert_int(result_parent, ==, papa);

  munit_assert_int(jacqueline, ==, maman);

  valid = str_to_Name("al", 2, &result);
  munit_assert_false(valid);

  Name *it = get_Name_iterator();
  munit_assert_int(it[0], ==, alfredo);
  munit_assert_int(it[1], ==, alphonse);
  munit_assert_int(it[2], ==, jacqueline);

  size_t size_name = get_Name_number();
  munit_assert_int(size_name, ==, 3);

  return 0;
}
