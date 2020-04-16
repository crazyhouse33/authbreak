#include "munit.h"
#include "argv.h"
#include "unistd.h"


extern char** environ;

void test_argp(){
	//this test mus be lunched 
	char* argp[]={"hy", "-te", NULL};
	size_t size=get_vector_count (argp);
	munit_assert_size(size,==,2);
	char ** crafted_args= get_argp_appended(argp);

	size_t size_env= get_vector_count(environ);

	size_t end=get_vector_count(crafted_args);
	munit_assert_size(end,>,2);

	munit_assert_size(size_env+size,==, end);

	munit_assert_string_equal(crafted_args[end-2], "hy");
	munit_assert_string_equal(crafted_args[end-1], "-te");
	munit_assert_ptr(crafted_args[end],==, NULL);

	for (size_t i=0; i<size_env; i++){
		munit_assert_string_equal(environ[i], crafted_args[i]);
	}


	char* mode[]={UNBUFFERED, DEFAULT_BUFFERING, FULLY_BUFFERED};
	char** env = build_argp_stdbuf_env(mode);
	size_t expected_new_size= size_env+3;
	munit_assert_size(expected_new_size, ==, get_vector_count(env));

	char* mode2[]={DEFAULT_BUFFERING, DEFAULT_BUFFERING, DEFAULT_BUFFERING};
	char** env2 = build_argp_stdbuf_env(mode2);
	size_t expected_new_size2= size_env;
	munit_assert_size(expected_new_size2, ==, get_vector_count(env2));

	char* mode3[]={DEFAULT_BUFFERING, DEFAULT_BUFFERING, "1042"};
	char** env3 = build_argp_stdbuf_env(mode3);
	size_t expected_new_size3= size_env+2;
	munit_assert_size(expected_new_size3, ==, get_vector_count(env3));
	munit_assert_string_equal(env3[expected_new_size3-1], "STDBUF_E=1042");
	munit_assert_string_equal(env3[expected_new_size3-2], "LD_PRELOAD="STDBUFLIBPATH );
	munit_assert_ptr(env3[expected_new_size3], ==,NULL);






}

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

	test_argp();


	return 0;
}




	
	

