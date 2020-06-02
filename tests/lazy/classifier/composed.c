#include "composed_classifier.h"
#include "munit.h"
#include "munit.h"
#include "output.h"

void test_classifier(Composed_classifier *classifier, bool expected, char *out_str, int time) {
  Output *out = malloc(sizeof(Output));
  out->out = out_str;
  out->term_time = time;
  bool res = classify_output(classifier, out);
  munit_assert_true(expected == res);
}

int main() {

  char *sucess_str[] = {"access granted"};
  int sucess_time[] = {2, 7};
  int num_str_suc = sizeof(sucess_str) / sizeof(char *);

  char *fail_str[] = {"nop", "rejected", "denied"};
  int num_str_fail = sizeof(fail_str) / sizeof(char *);

  Composed_classifier *the_classifier = malloc(sizeof(Composed_classifier));
  the_classifier->strcmp_class = malloc(sizeof(Classifier_strcmp) * (num_str_suc + num_str_fail));
  int i;
  for (i = 0; i < num_str_suc; i++) {
    Classifier_strcmp_init(&the_classifier->strcmp_class[i], true, sucess_str[i]);
  }
  for (; i < num_str_fail + num_str_suc; i++) {
    Classifier_strcmp_init(&the_classifier->strcmp_class[i], false, fail_str[i - num_str_suc]);
  }

  the_classifier->time_class = malloc(sizeof(Classifier_time) * 2);
  Classifier_time_init(&the_classifier->time_class[0], true, sucess_time[0], superior_or_eq);

  Classifier_time_init(&the_classifier->time_class[1], true, sucess_time[1], inferior_or_eq);

  the_classifier->num_strcmp = num_str_suc + num_str_fail;
  the_classifier->num_time = 2;

  test_classifier(the_classifier, false, "denied", 5);
  test_classifier(the_classifier, true, "access granted", 5);
  test_classifier(the_classifier, false, "auth broken", 1);
  test_classifier(the_classifier, false, "access granted", 11);

  return 0;
}
