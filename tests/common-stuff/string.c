#include "stringmy.h"
#include "munit.h"

int main(){
	char strip_me_array[]= "  hey, how you doing? \t";// this is necessary cause literal are not writable in C.
	char* strip_me= &strip_me_array[0];
	left_trim_in_place(&strip_me);
	munit_assert_string_equal(strip_me, "hey, how you doing? \t");


	char* end=strip_me+ strlen(strip_me)-1;
	point_to_last_white(&end);


	munit_assert_char(*(end-1),==, '?');
	munit_assert_string_equal(strip_me, "hey, how you doing? \t");

	char* end2=strip_me+ strlen(strip_me)-1;
	right_trim_in_place(&end2);
	munit_assert_string_equal(strip_me, "hey, how you doing?");

	char  strip_me2_array[]= "  hey, how you doing? \t";
	char* strip_me2= &strip_me2_array[0];
	char* left_striped= left_trim(strip_me2);
	munit_assert_string_equal(strip_me2, "  hey, how you doing? \t");
	munit_assert_string_equal(left_striped, "hey, how you doing? \t");

	char* striped= trim(strip_me2, strip_me2 + strlen(strip_me2));
	munit_assert_string_equal(striped, "hey, how you doing?");
	munit_assert_string_equal(strip_me2, "  hey, how you doing? \t");
	return 0;
}
