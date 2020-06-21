#include "munit.h"
#include "or_combined_classifier.h"
#include "output.h"

void test_classifier(Or_combined_classifier *classifier, bool expected, char *out_str, int time, int status) {
  Output *out = malloc(sizeof(Output));
  out->out = out_str;
  out->term_time = time;
  out->exit_status = status;
  bool res = or_combined_classifier_classify_output(classifier, out);
  munit_assert_true(expected == res);
}

int main() {

  char *sucess_str[] = {"access granted"};
  int sucess_time[] = {2, 7};
  int num_str_suc = sizeof(sucess_str) / sizeof(char *);

  char *fail_str[] = {"nop", "rejected", "denied"};
  int num_str_fail = sizeof(fail_str) / sizeof(char *);

  int sucess_status[] = {-2, 4};
  int num_status = sizeof(sucess_status) / sizeof(int);

  Composed_classifier *the_classifier = composed_classifier_new(true);
  the_classifier->stringcmp_class = malloc(sizeof(Classifier_stringcmp) * (num_str_suc + num_str_fail));
  int i;
  for (i = 0; i < num_str_suc; i++) {
    classifier_stringcmp_init(&the_classifier->stringcmp_class[i], true, equal, sucess_str[i]);
  }
  for (; i < num_str_fail + num_str_suc; i++) {
    classifier_stringcmp_init(&the_classifier->stringcmp_class[i], false, equal, fail_str[i - num_str_suc]);
  }

  the_classifier->time_class = malloc(sizeof(Classifier_diff_long) * 2);
  classifier_diff_long_init(&the_classifier->time_class[0], true, superior_or_eq, sucess_time[0]);

  classifier_diff_long_init(&the_classifier->time_class[1], true, inferior_or_eq, sucess_time[1]);

  the_classifier->status_diff_class = malloc(sizeof(Classifier_diff_int) * 2);
  classifier_diff_int_init(&the_classifier->status_diff_class[0], true, superior_or_eq, sucess_status[0]);
  classifier_diff_int_init(&the_classifier->status_diff_class[1], true, inferior_or_eq, sucess_status[1]);

  the_classifier->num_stringcmp = num_str_suc + num_str_fail;
  the_classifier->num_time = 2;
  the_classifier->num_status_diff = 2;

  // status must be -18
  Composed_classifier *the_classifier2 = composed_classifier_new(false);
  the_classifier2->num_status_eq = 1;
  the_classifier2->status_eq_class = malloc(sizeof(Classifier_eq_int));
  classifier_eq_int_init(&the_classifier2->status_eq_class[0], false, equal, -18);

  Composed_classifier *the_classifier3 = composed_classifier_new(false);
  the_classifier3->num_stringcmp = 1;
  the_classifier3->stringcmp_class = malloc(sizeof(Classifier_stringcmp));
  classifier_stringcmp_init(&the_classifier3->stringcmp_class[0], false, equal, "backdoor");

  Or_combined_classifier *or_class = or_combined_classifier_new();
  or_combined_classifier_add(or_class, the_classifier);
  or_combined_classifier_add(or_class, the_classifier2);
  or_combined_classifier_add(or_class, the_classifier3);

  test_classifier(or_class, true, "backdoor", 456223, -79);
  test_classifier(or_class, true, "backdoor", 456223, -18);
  test_classifier(or_class, true, "backdoor", 5, 0);
  test_classifier(or_class, true, "bazfefsqckdoor", -79, -18);
  test_classifier(or_class, true, "access granted", 5, 2);
  test_classifier(or_class, false, "zaesf", 10, 14);

  return 0;
}
