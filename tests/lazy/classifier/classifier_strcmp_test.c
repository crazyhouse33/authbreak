#include "munit.h"
#include "strcmp_classifier.h"

void generate_test(char *res, char *target, bool expected) {
  Classifier_stringcmp *class = malloc(sizeof(Classifier_stringcmp));
  classifier_stringcmp_init(class, true, equal, target);
  bool test = classifier_stringcmp_classify(class, res);
  munit_assert_true(expected == test);

  Classifier_stringcmp *class_false = malloc(sizeof(Classifier_stringcmp));
  classifier_stringcmp_init(class_false, false, equal,target);
  bool test2 = classifier_stringcmp_classify(class_false, res);
  munit_assert_false(test2 == expected);

Classifier_stringcmp *class_true_false = malloc(sizeof(Classifier_stringcmp));
  classifier_stringcmp_init(class_true_false, true, not_equal, target);
  bool test3 = classifier_stringcmp_classify(class_true_false, res);
  munit_assert_false(expected == test3);

 Classifier_stringcmp *class_false_false = malloc(sizeof(Classifier_stringcmp));
  classifier_stringcmp_init(class_false_false, false, not_equal,target);
  bool test4 = classifier_stringcmp_classify(class_false_false, res);
  munit_assert_true(test4 == expected);
}

int main() {
  generate_test("tot", "toto", false);
  generate_test("", "", true);
  generate_test("", "ta", false);

  generate_test("nop", "no", false);

  generate_test("tatatata", "tatatata", true);

  return 0;
}
