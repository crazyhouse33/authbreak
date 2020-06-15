#include "munit.h"
#include "output_classifier_front.h"

void generate_test(Composed_classifier *classifier, char *parse_str, int expected_time, int expected_strcmp) {
  parse_classifier_str(classifier, parse_str);
  munit_assert_int(classifier->num_stringcmp, ==, expected_strcmp);
  munit_assert_int(classifier->num_time, ==, expected_time);
}

//We declare it there cause this function should be static, however if we want to be able to test it in an unit tets, we must export it. So we do it but dont expose it in the interface, stil removing the warning
Authorized_classifier_type_key classifier_separate_classifier( char *class_string, size_t until, char **class_value, size_t *value_size, int* class_op);

void generate_test_separation(char* test_str, int expected_type, int expected_op, char* expected_value ){
	size_t until=strlen(test_str);
  char *value; 
  size_t value_size;
  int op;
  Authorized_classifier_type_key type =  classifier_separate_classifier(test_str, until, &value, &value_size, &op);
  munit_assert_int(expected_type,==,type);
  munit_assert_int(op,==,expected_op);
  munit_assert_string_equal(value,expected_value);
}
int main() {
	Composed_classifier *classifier = calloc(1, sizeof(Composed_classifier));
	classifier->time_class = malloc(sizeof(Classifier_time) * 2);
	classifier->stringcmp_class = malloc(sizeof(Classifier_stringcmp) * 2);

	generate_test(classifier, "out_eq==tatata", 0, 1);
	generate_test(classifier, "time  <= 8", 1, 1);
	generate_test(classifier, "! time  >= 14", 2, 1);
	generate_test(classifier, "!  out_eq=totot  ", 2, 2);
	generate_test(classifier, "!  out_eq==", 2, 3);
	generate_test(classifier, "out_eq!= ", 2, 4);

	generate_test_separation("time < 18", time, inferior_strict, "18");
	generate_test_separation("time  < 18", time, inferior_strict, "18");
	generate_test_separation("time  <= 18", time, inferior_or_eq, "18");
	generate_test_separation("time  > 18", time, superior_strict, "18");
	generate_test_separation("time  >=   18", time, superior_or_eq, "18");

	generate_test_separation("out_eq == 18", stringcmp, equal, "18");
	generate_test_separation("out_eq!= 18", stringcmp, not_equal, "18");

	return 0;
}
