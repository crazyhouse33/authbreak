#include "munit.h"
#include "argv.h"
#include "unistd.h"


extern char** environ;

void test_argp(){
	//this test mus be lunched 
	char* argp[]={"hy", "-te", NULL};
	size_t size=get_vector_count (argp);
	munit_assert_size(size,==,2);
	char ** crafted_args= get_envp_appended(argp);

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


	//testing stdbufenv building
	
	#if LIBSTDBUF_IS_FOUND
	char* mode[]={UNBUFFERED, DEFAULT_BUFFERING, "65536"};
	char** env = build_stdbuf_exec_envp(mode);
	size_t expected_new_size= size_env+3;
	munit_assert_size(expected_new_size, ==, get_vector_count(env));

	char* mode2[]={DEFAULT_BUFFERING, DEFAULT_BUFFERING, DEFAULT_BUFFERING};
	char** env2 = build_stdbuf_exec_envp(mode2);
	size_t expected_new_size2= size_env;
	munit_assert_size(expected_new_size2, ==, get_vector_count(env2));

	char* mode3[]={DEFAULT_BUFFERING, DEFAULT_BUFFERING, "1042"};
	char** env3 = build_stdbuf_exec_envp(mode3);
	size_t expected_new_size3= size_env+2;
	munit_assert_size(expected_new_size3, ==, get_vector_count(env3));
	munit_assert_string_equal(env3[expected_new_size3-1], "_STDBUF_E=1042");
	munit_assert_string_equal(env3[expected_new_size3-2], "LD_PRELOAD="LIBSTDBUF_PATH );
	munit_assert_ptr(env3[expected_new_size3], ==,NULL);
	#else
	char* mode[]={UNBUFFERED, DEFAULT_BUFFERING, "65536"};
	char** env = build_stdbuf_exec_envp(mode);
	munit_assert_ptr(env,==,NULL); 
	#endif

}

void assert_arg_equal(char** arg1, char** arg2){
	size_t s1=get_vector_count(arg1);

	munit_assert_size(s1,==,get_vector_count(arg2));
	for (size_t i=0; i< s1;i++){
		munit_assert_string_equal(arg1[i], arg2[i]);
	}

}

void test_base(){


	char* vec[] = {"authbreak", "--prompt", "18", "curl -f tamere", "--fail", "hey", NULL};
	char ** vec1= (char**)vec;
	size_t size=get_vector_count (vec1);
	munit_assert_size(size,==,6);

	char** clone= dup_arg_vector(vec1);
	assert_arg_equal(clone, vec1);
	munit_assert_ptr(clone,!=,vec1);


	char* exepected[]= {"authbreak", "--prompt", "18", "curl -f tamere", "--fail", "hey", "tamere", "tonpere", NULL};


	char* vec2[] = {"tamere", "tonpere", NULL};
	char** concat= concatenation_arg_vector(vec1, vec2);
	assert_arg_equal(exepected, concat);
	munit_assert_ptr(concat,!=,vec1);
	assert_arg_equal(exepected,concat);

	concatenate_arg_vector(&clone,vec2);
	assert_arg_equal(clone, exepected);


}


int main(){
	char* command= "authbreak --prompt 18 'curl -f tamere' --fail hey";
	size_t argc;
	char** argv= argv_vector_from_string(command, &argc);
	char* expected[] = {"authbreak", "--prompt", "18", "curl -f tamere", "--fail", "hey", NULL};
	size_t expected_size = sizeof(expected)/sizeof(expected[0]);
	size_t i=0;
	for (; i< expected_size-1;i++){
		munit_assert_string_equal(argv[i], expected[i]);
	}

	munit_assert_ptr(argv[i],==, expected[i]);
	munit_assert_int(argc, ==, expected_size-1);

	test_base();

	test_argp();


	return 0;
}







