#include "trim_string.h"
#include "munit.h"

int main(){
	char strip_me_array[]= "  hey, how you doing? \t";// this is necessary cause literal are not writable in C.
	char* strip_me= &strip_me_array[0];
	//left_trim_in_place
	left_trim_in_place(&strip_me);
	munit_assert_string_equal(strip_me, "hey, how you doing? \t");


	char* end=strip_me+ strlen(strip_me)-1;
	point_to_last_white(&end);


	munit_assert_char(*(end-1),==, '?');
	munit_assert_string_equal(strip_me, "hey, how you doing? \t");

	//right_trim_in_place
	char* end2=strip_me+ strlen(strip_me)-1;
	right_trim_in_place(&end2);
	munit_assert_string_equal(strip_me, "hey, how you doing?");

	//left_trim
	char  strip_me2_array[]= "  hey, how you doing? \t";
	char* strip_me2= &strip_me2_array[0];
	char* left_striped= left_trim(strip_me2);
	munit_assert_string_equal(strip_me2, "  hey, how you doing? \t");
	munit_assert_string_equal(left_striped, "hey, how you doing? \t");

	//trim
	char* striped= trim(strip_me2, strip_me2 + strlen(strip_me2));
	munit_assert_string_equal(striped, "hey, how you doing?");
	munit_assert_string_equal(strip_me2, "  hey, how you doing? \t");

	//trim_in_place_preserve_right
	char  strip_me3_array[]= "  hey, how you doing? \t";
	char* strip_me3= &strip_me3_array[0];
	char* end3=strip_me3+ strlen(strip_me3)-1;
	char* end3_old= end3;
	trim_in_place_preserve_right(&strip_me3, end3);
	munit_assert_string_equal(strip_me3, "hey, how you doing?");
	munit_assert_ptr(end3,==,end3_old);


	//trim_in_place_preserve_left
	char  strip_me4_array[]= "  hey, how you doing? \t";
	char* strip_me4= &strip_me4_array[0];
	char* old_strip4= strip_me4;
	char* end4=strip_me4+ strlen(strip_me4)-1;
	char* result=trim_in_place_preserve_left(strip_me4, &end4);
	munit_assert_string_equal(result, "hey, how you doing?");
	munit_assert_ptr(old_strip4,==,strip_me4);
	munit_assert_char(*(end4),==, 0);
	return 0;


}

	
