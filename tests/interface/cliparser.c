#include "cliparser.h"
#include "munit.h"
#include <wordexp.h>
#include <stdio.h>
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
	char command[]="curl -F password={/opt/secu/wordlist/rockme.txt} 'https://example.com/upload.cgi' --success regexp --fail ";
	Sysarg sysarg= make_args(command);
	Arguments* args = get_arguments ( sysarg.argc, sysarg.argv);
	munit_assert_int(2, ==, args->prompt_cpt);
	munit_assert_int(1, ==, args->sucess_cpt);
	munit_assert_int(0, ==, args->fail_cpt);
	exit(0);

}
