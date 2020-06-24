#include "strcmp_classifier_front.h"
#include "strcmp_classifier.h"
#include "munit.h"

void generate_test(char *parse_str, char *expected_target) {

  Classifier_stringcmp *classifier = malloc(sizeof(Classifier_stringcmp));
  char* target=parse_stringcmp_classifier_str_value(parse_str);
  munit_assert_string_equal(target, expected_target);
}
int main() {
  generate_test("abcd", "abcd");
  generate_test("aba cd", "aba cd");
  generate_test("", "");
  return 0;
}
