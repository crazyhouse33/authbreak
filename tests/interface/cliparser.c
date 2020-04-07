#include "cliparser.h"
#include "munit.h"
#include <wordexp.h>
#include <stdio.h>
#include <argp.h> //argp flags
// https://www.unix.com/programming/126160-building-argc-argv-style-structure-string-char.html
/* using the default shell parser - no extra code required */

typedef struct Sysarg 
{
    int argc;
    char** argv;
} Sysarg;


Sysarg make_args( char *string)
{
    wordexp_t p;
    switch (wordexp(string, &p, 0)){
	    case 0:
break;
	case WRDE_BADCHAR:
	    fprintf(stderr, "ERROR: One of the unquoted characters- <newline>, '|', '&', ';', '<', '>', '(', ')', '{', '}' - appears in words in an inappropriate context.");
	    break;
	case WRDE_NOSPACE:
	    fprintf(stderr, "ERROR: Attempt to allocate memory failed.");
break;
	case WRDE_SYNTAX:
	    fprintf(stderr, "ERROR: Shell syntax error, such as unbalanced parentheses or unterminated string.");
	    break;
	default:
	    fprintf(stderr, "ERROR: Attempt to allocate memory failed.");
    }
    Sysarg sysarg= {p.we_wordc, p.we_wordv};
    return sysarg;


}


int main() {	
	//testing public interface
	char command[]="authbreak 'curl -F password=password https://example.com/upload.cgi' --success regexp -s gotprompt -f outpuy=18  --fail hopeless=29 -p test --prompt tamere=118";
	Sysarg sysarg= make_args(command);
	Arguments* args = get_arguments ( sysarg.argc, sysarg.argv,0 );
	munit_assert_int(2, ==, args->prompt_cpt);
	munit_assert_int(2, ==, args->sucess_cpt);
	munit_assert_int(2, ==, args->fail_cpt);
	munit_assert_string_equal(args->command_line, "curl -F password=password https://example.com/upload.cgi");
	munit_assert_string_equal(args->prompt[0], "test");
	munit_assert_string_equal(args->prompt[1],  "tamere=118");
	munit_assert_string_equal(args->fail[0],  "outpuy=18");
	munit_assert_string_equal(args->fail[1],  "hopeless=29");
	munit_assert_string_equal(args->sucess[0], "regexp");
	munit_assert_string_equal(args->sucess[1],  "gotprompt");

	exit(0);

}
