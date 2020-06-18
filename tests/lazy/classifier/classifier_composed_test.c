#include "composed_classifier.h"
#include "munit.h"
#include "munit.h"
#include "output.h"

void test_classifier(Composed_classifier *classifier, bool expected, char *out_str, int time, int status) {
  Output *out = malloc(sizeof(Output));
  out->out = out_str;
  out->term_time = time;
  out->exit_status = status;
  bool res = classify_output(classifier, out);
  munit_assert_true(expected == res);
}

int main() {

  char *sucess_str[] = {"access granted"};
  int sucess_time[] = {2, 7};
  int num_str_suc = sizeof(sucess_str) / sizeof(char *);

  char *fail_str[] = {"nop", "rejected", "denied"};
  int num_str_fail = sizeof(fail_str) / sizeof(char *);

  int sucess_status[]={-2, 4};
  int num_status = sizeof(sucess_status) / sizeof(int);

  Composed_classifier *the_classifier = composed_classifier_new();
  the_classifier->stringcmp_class = malloc(sizeof(Classifier_stringcmp) * (num_str_suc + num_str_fail));
  int i;
  for (i = 0; i < num_str_suc; i++) {
    classifier_stringcmp_init(&the_classifier->stringcmp_class[i], true, equal, sucess_str[i]);
  }
  for (; i < num_str_fail + num_str_suc; i++) {
    classifier_stringcmp_init(&the_classifier->stringcmp_class[i], false, equal, fail_str[i - num_str_suc]);
  }

  the_classifier->time_class = malloc(sizeof(Classifier_diff_long) * 2);
  classifier_diff_long_init(&the_classifier->time_class[0], true, superior_or_eq,sucess_time[0] );

  classifier_diff_long_init(&the_classifier->time_class[1], true, inferior_or_eq,sucess_time[1]);


  the_classifier->status_diff_class = malloc(sizeof(Classifier_diff_int) * 2);
  classifier_diff_int_init(&the_classifier->status_diff_class[0], true, superior_or_eq,sucess_status[0]);
  classifier_diff_int_init(&the_classifier->status_diff_class[1], true, inferior_or_eq,sucess_status[1]);



  the_classifier->num_stringcmp = num_str_suc + num_str_fail;
  the_classifier->num_time = 2;
  the_classifier->num_status_diff= 2;

  test_classifier(the_classifier, false, "denied", 5, -2);
  test_classifier(the_classifier, true, "access granted", 5,-1);
  test_classifier(the_classifier, false, "auth broken", 1,0);
  test_classifier(the_classifier, false, "access granted", 11,1);
  test_classifier(the_classifier, false, "access granted", 5,-3);

  return 0;
}
