#include "strcmp_classifier_front.h"
#include "munit.h"

void generate_test(char* parse_str, char* expected_target){

	Classifier_stringcmp* classifier= malloc(sizeof(Classifier_stringcmp));
parse_stringcmp_classifier_str( classifier, parse_str );
munit_assert_string_equal(classifier->target_string,expected_target);

}
int main(){
	generate_test("abcd", "abcd");
	generate_test("aba cd", "aba cd");
	return 0;
}

