#include "munit.h"

#include "diff_long_classifier.h"

void generate_test(long got,  Operator op, long target, bool expected) {
  Classifier_diff_long *class = malloc(sizeof(Classifier_diff_long));
  classifier_diff_long_init(class, true,  op, target);
  bool test = classifier_diff_long_classify(class, got);
  munit_assert_true(expected == test);

  Classifier_diff_long *class_false = malloc(sizeof(Classifier_diff_long));
  classifier_diff_long_init(class_false, false, op,target);
  bool test2 = classifier_diff_long_classify(class_false, got);
  munit_assert_false(test2 == expected);
}

int main() {
  generate_test(18,  inferior_or_eq, 18,true);
  generate_test(18,  inferior_or_eq, 19,true);
  generate_test(18,  inferior_or_eq, 17,false);
                                        
  generate_test(18,  inferior_strict,17,false);
  generate_test(18,  inferior_strict,18,false);
  generate_test(18,  inferior_strict,19,true);
                                        
  generate_test(18,  superior_strict,17,true);
  generate_test(18,  superior_strict,18,false);
  generate_test(18,  superior_strict,19,false);
                                        
  generate_test(18,  superior_or_eq, 18,true);
  generate_test(18,  superior_or_eq, 19,false);
  generate_test(18,  superior_or_eq, 17,true);

  generate_test(1, superior_strict,0, true);
  generate_test(0, inferior_strict, 1, true);

  return 0;
}
