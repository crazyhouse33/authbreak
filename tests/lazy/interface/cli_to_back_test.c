#include "argument_to_backend.h"
#include "munit.h"

void generate_test(char **success, size_t success_num, size_t expected_time, size_t expected_string) {
  Arguments *arg = malloc(sizeof(Arguments));
  memcpy(arg->sucess, success, sizeof(char *) * success_num);
  arg->sucess_cpt = success_num;
  Composed_classifier *classifier = arguments_to_composed_classifier(arg);
  munit_assert_size(classifier->num_stringcmp, ==, expected_string);
  munit_assert_size(classifier->num_time, ==, expected_time);
}

int main() {
  char *success[] = {"! out_eq=19", "out_eq=17", "time= <=4"};
  generate_test(success, 3, 1, 2);

  char *success2[] = {"time= <=4"};
  generate_test(success2, 1, 1, 0);
  return 0;
}
