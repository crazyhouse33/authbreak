#include "output_classifier_front.h"
#include "munit.h"

void generate_test(Composed_classifier* classifier, char* parse_str, int expected_time, int expected_strcmp){
parse_classifier_str(classifier, parse_str);
munit_assert_int(classifier->num_stringcmp,==, expected_strcmp);
munit_assert_int(classifier->num_time,==, expected_time);

}
int main(){
	Composed_classifier* classifier= calloc (1,sizeof(Composed_classifier));
	classifier->time_class = malloc(sizeof(Classifier_time) * 2);
	classifier->stringcmp_class = malloc(sizeof(Classifier_stringcmp) * 2);

	generate_test(classifier, "out_eq=tatata", 0,1);
	generate_test(classifier, "time = <= 8", 1,1);
	generate_test(classifier, "! time = >= 14", 2,1);
	generate_test(classifier, "!  out_eq=totot  ", 2,2);
	return 0;
}

