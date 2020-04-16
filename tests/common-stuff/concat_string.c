#include "concat_string.h"
#include "munit.h"
#include <string.h>

int main(){
	char* test=strdup("tata");
	char* test2=strdup("toto");
	char* other= sstrcat_copy(test, test2);

	munit_assert_string_equal(other, "tatatoto");
	munit_assert_string_equal(test, "tata");

	/*C dont allow that (realloc on literal)*/
	char* inplace= sstrcat(test, test2);

	munit_assert_string_equal(inplace, "tatatoto");
	munit_assert_string_equal(test, "tatatoto");


}
