#include "cliparser.h"
#include "munit.h"
// https://www.unix.com/programming/126160-building-argc-argv-style-structure-string-char.html
/* using the default shell parser - no extra code required */
void make_args(char **argv, int *argc, char *string)
{
		char tmp[256]={0x0};
		FILE *cmd=NULL;
		int i=0;
		char *p=NULL;
		
		sprintf(tmp, "set - %s && for i in %c$@%c;\n do\n echo $i\ndone", 
		        string, '"', '"');
		cmd=popen(tmp, "r");
		while (fgets(tmp, sizeof(tmp), cmd)!=NULL)
		{
		    p=strchr(tmp, '\n');
		    if (p!=NULL) *p=0x0;
				strcpy(argv[i++], tmp);
		}
		*argc=i;
}

int main(int argc, char **argv) {	
	//testing public interface
	int argc;
	char** argv;
	char* command="curl -F password={/opt/secu/wordlist/rockme.txt} https://example.com/upload.cgi' --success regexp --fail "
	make_args(&argc, argv, command);
	Arguments* args = get_arguments (int argc, char **argv);
	munit_assert_int(2, ==, args->prompt_ctp);
	munit_assert_int(1, ==, args->sucess_ctp);
	munit_assert_int(0, ==, args->fail_ctp);
	exit(0);

}
