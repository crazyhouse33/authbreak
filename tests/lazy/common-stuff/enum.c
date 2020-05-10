#include "enum.h"
#include "munit.h"

CREATE_ENUM(Parent, tamere, tonpere);
ASSOCIATE_E(Parent, "papa", "maman");

CREATE_ENUM(Name, alfredo, alphonse);
ASSOCIATE_E(Name, "al", "alp");

int main() {
  Name result;
  bool valid valid = str_to_Name("al", 2, &result);
  munit_assert_true(valid);

  munit_assert_int(result, ==, alfredo);

  Parent result_parent;
  valid = str_to_Parent("papa", 4, &result_parent);
  munit_assert_true(valid);
  munit_assert_int(result_parent, ==, tonpere);

  valid = str_to_Name("alp", 3, &result);
  munit_assert_true(valid);
  munit_assert_int(result, ==, alphonse);

  Parent result_invalid;
  valid = str_to_Parent("papa", 4, &result_invalid);
  munit_assert_false(valid);

  valid = str_to_Parent("maman", 5, &result_parent);
  munit_assert_true(valid);
  munit_assert_int(result_parent, ==, tamere);
  return 0;
}
