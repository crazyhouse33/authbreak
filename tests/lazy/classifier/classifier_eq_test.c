#include "munit.h"

#include "eq_int_classifier.h"

void generate_test(int got,  Operator op, int target, bool expected) {
  Classifier_eq_int *class = malloc(sizeof(Classifier_eq_int));
  classifier_eq_int_init(class, true,  op, target);
  bool test = classifier_eq_int_classify(class, got);
  munit_assert_true(expected == test);

  Classifier_eq_int *class_false = malloc(sizeof(Classifier_eq_int));
  classifier_eq_int_init(class_false, false, op,target);
  bool test2 = classifier_eq_int_classify(class_false, got);
  munit_assert_false(test2 == expected);
}

int main() {
  generate_test(18, equal, 18,true);
  generate_test(18,  not_equal, 18,false);
  generate_test(18,  not_equal, 17,true);
  generate_test(18,  not_equal, 18,false);

  generate_test(-1, equal, -1,true);
  generate_test(-1,  not_equal, -1,false);
  generate_test(0,  not_equal, -1,true);
  generate_test(-1,  not_equal, -1,false);
                                        
  return 0;
}
