#include "time_classifier_front.h"
#include "munit.h"

void generate_test(char* parse_str, int expected_target, int expected_adder, int expected_mult){

	Classifier_time* classifier= malloc(sizeof(Classifier_time));
parse_time_classifier_str( classifier, parse_str );
munit_assert_int(classifier->target_int,==,expected_target);
munit_assert_int(classifier->multiplier,==, expected_mult);
munit_assert_int(classifier->adder,==, expected_adder);

}
int main(){
	generate_test("<=15", 15, 1, 1);
	generate_test(">15", 15, 0, -1);
	generate_test(">=15", 15, -1, -1);
	generate_test(">=0", 0, -1, -1);
	generate_test(">=  0", 0, -1, -1);
	return 0;
}

