#include "munit.h"
#include "time_classifier.h"

void generate_test(int target_time, int time, Supported_operator op, bool expected) {
  Output *out = malloc(sizeof(Output));
  out->term_time = time;
  Classifier_time *class = malloc(sizeof(Classifier_time));
  Classifier_time_init(class, true, target_time, op);
  bool test = Classifier_time_classify(class, out);
  munit_assert_true(expected == test);

  Classifier_time *class_false = malloc(sizeof(Classifier_time));
  Classifier_time_init(class_false, false, target_time, op);
  bool test2 = Classifier_time_classify(class_false, out);
  munit_assert_false(test2 == expected);
}

int main() {
  generate_test(18, 18, inferior_or_eq, true);
  generate_test(18, 19, inferior_or_eq, false);
  generate_test(18, 17, inferior_or_eq, true);

  generate_test(18, 17, inferior_strict, true);
  generate_test(18, 18, inferior_strict, false);
  generate_test(18, 19, inferior_strict, false);

  generate_test(18, 17, superior_strict, false);
  generate_test(18, 18, superior_strict, false);
  generate_test(18, 19, superior_strict, true);

  generate_test(18, 18, superior_or_eq, true);
  generate_test(18, 19, superior_or_eq, true);
  generate_test(18, 17, superior_or_eq, false);

  generate_test(0, 1, superior_strict, true);
  generate_test(1, 0, inferior_strict, true);

  return 0;
}
