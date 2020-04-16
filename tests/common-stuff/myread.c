#include "myread.h"
#include <stdio.h>
#include "munit.h"
#include <unistd.h>
#include <string.h>


int main(){
	char* expected="import sys\n\nwith open('testfile','w') as f:\n    print(*sys.argv, file=f)\n    print(input(), file=f)\n    print(input(), file=f)\n    print(input(), file=f)\n\nprint(\"test sdout recup\")\nprint(\"test stderr recup\", file=sys.stderr)\n";
	size_t max=1;
	size_t old_max=max;
	char* buff = malloc(sizeof(char) * max);
	//Output* out=executor_get_output("/opt/handCraftedUtilityShit/authbreak/tests/execution/a.out test.py test", prompt, 3, 10);
	
	FILE* fp=fopen("test.py", "r");

	char buffer[500];
	/* Read and display data */
	size_t size=fread(buffer, 1, 500, fp);//read the file
	buffer[size]=0;

	int fake_pipe[2];
	pipe(fake_pipe);
	
	//populate fake pipe
	write(fake_pipe[1], buffer, strlen(buffer));
	close(fake_pipe[1]);

	int fd= fake_pipe[0];


	size_t readed=0;

	size_t oldmax=max;
	size_t nb= read_append(fd, &buff, &readed, &max);
	munit_assert_size(nb,==,1);
	munit_assert_size(readed,==,1);
	munit_assert_int(strncmp(buff,expected,1),==,0);
	munit_assert_size(max,>,old_max);

	while (nb>0){
		old_max=max;
		nb=read_append(fd,&buff,&readed,&max);
	}
	munit_assert_string_equal(buff, expected);
	munit_assert_size(strlen(buff), == , readed);
	fclose(fp);
	return 0;

}
