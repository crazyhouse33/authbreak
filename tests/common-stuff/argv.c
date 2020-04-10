#include "stringmy.h"
#include "munit.h"
#include "argv.h"

int main(){
	char* command= "authbreak --prompt 18 'curl -f tamere' --fail hey";
	int argc;
	char** argv= buildargv(command, &argc);
	char* expected[] = {"authbreak", "--prompt", "18", "curl -f tamere", "--fail", "hey", NULL};
	size_t expected_size = sizeof(expected)/sizeof(expected[0]);
	size_t i=0;
	for (; i< expected_size-1;i++){
		munit_assert_string_equal(argv[i], expected[i]);
	}

	munit_assert_ptr(argv[i],==, expected[i]);
	munit_assert_int(argc, ==, expected_size-1);

	return 0;
}


	
	

