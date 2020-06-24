#include "time_classifier_front.h"
#include "diff_long_classifier.h"
#include "munit.h"


void generate_test_op(Supported_time_operator op, long expected_target, long expected_adder, long  expected_mult) {
 
  Classifier_diff_long *classifier = malloc(sizeof(Classifier_diff_long));
  classifier_diff_long_init_core_op(classifier, op);
  munit_assert_int(classifier->multiplier, ==, expected_mult);
  munit_assert_int(classifier->adder, ==, expected_adder);
 }


void generate_test_parse(char *parse_str,  int expected_target) {

  Classifier_diff_long *classifier = malloc(sizeof(Classifier_diff_long));
  int target = parse_time_classifier_str_value( parse_str);
  munit_assert_int(target, ==, expected_target);
}
int main() {
  generate_test_parse("146", 146);
  generate_test_parse("0", 0);

  generate_test_op(inferior_or_eq, 15, 1, 1);
  generate_test_op(superior_strict, 15, 0, -1);
  generate_test_op(superior_or_eq, 15, -1, -1);
  generate_test_op(superior_or_eq, 0, -1, -1);
  generate_test_op(inferior_strict, 0, 0, 1);
  return 0;
}


