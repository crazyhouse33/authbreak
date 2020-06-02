#include "munit.h"
#include "strcmp_classifier.h"

void generate_test(char *res, char *target, bool expected) {
  Output *out = malloc(sizeof(Output));
  out->out = res;
  Classifier_strcmp *class = malloc(sizeof(Classifier_strcmp));
  Classifier_strcmp_init(class, true, target);
  bool test = Classifier_strcmp_classify(class, out);
  munit_assert_true(expected == test);

  Classifier_strcmp *class_false = malloc(sizeof(Classifier_strcmp));
  Classifier_strcmp_init(class_false, false, target);
  bool test2 = Classifier_strcmp_classify(class_false, out);
  munit_assert_false(test2 == expected);
}

int main() {
  generate_test("tot", "toto", false);
  generate_test("", "", true);
  generate_test("", "ta", false);

  generate_test("nop", "no", false);

  generate_test("tatatata", "tatatata", true);

  return 0;
}
