#include "executor.h"
#include <stdio.h>
#include "munit.h"

int main(){
	char* prompt[] =
	{ "Hello",
		"test",
		"goodbye"
	};
	executor_exec("python test.py test", prompt,10);
	
	FILE *fp=fopen("test", "r");
	char buffer[200];


	/* Read and display data */
	fread(buffer, 1, 200, fp);
	fclose(fp);
	munit_assert_string_equal( buffer, "test\nHello\ntest\ngoodbye");

}
