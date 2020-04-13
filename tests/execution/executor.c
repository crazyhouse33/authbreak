#include "executor.h"
#include <stdio.h>
#include "munit.h"

int main(){
	char* prompt[] =
	{ 	"Hello\n",
		"test\n",
		"goodbye\n"
	};
	//Output* ou=executor_get_output("/opt/handCraftedUtilityShit/authbreak/tests/execution/a.out test.py test", prompt, 3, 10);
	Output* out=executor_get_output("python3.7 test.py test", prompt, 3, 10);
	
	FILE *fp=fopen("testfile", "r");
	char buffer[200];


	/* Read and display data */
	size_t size=fread(buffer, 1, 200, fp);
	buffer[size]=0;
	fclose(fp);
	munit_assert_string_equal( buffer, "test.py test\nHello\ntest\ngoodbye\n");

	
	munit_assert_string_equal( out->out, "test sdout recup\ntest stderr recup");

}
