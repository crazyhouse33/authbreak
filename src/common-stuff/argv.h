
/*This module provide functions to work with entry variable of process, such as argv and arp*/

#include <stdlib.h> 
#include <string.h>
#include <ctype.h>


/*
NAME

	buildargv -- build an argument vector from a string

SYNOPSIS

	char **buildargv (char* sp)

DESCRIPTION

	Given a pointer to a string, parse the string extracting fields
	separated by whitespace and optionally enclosed within either single
	or double quotes (which are stripped off), and build a vector of
	pointers to copies of the string for each field.  The input string
	remains unchanged.

	All of the memory for the pointer array and copies of the string
	is obtained from malloc.  All of the memory can be returned to the
	system with the single function call freeargv, which takes the
	returned result of buildargv, as it's argument.

	The memory for the argv array is dynamically expanded as necessary.

RETURNS

	Returns a pointer to the argument vector if successful. Returns NULL
	if the input string pointer is NULL or if there is insufficient
	memory to complete building the argument vector.

NOTES

	In order to provide a working buffer for extracting arguments into,
	with appropriate stripping of quotes and translation of backslash
	sequences, we allocate a working buffer at least as long as the input
	string.  This ensures that we always have enough space in which to
	work, since the extracted arg is never larger than the input string.

	If the input is a null string (as opposed to a NULL pointer), then
	buildarg returns an argv that has one arg, a null string.

	Argv is always kept terminated with a NULL arg pointer, so it can
	be passed to freeargv at any time, or returned, as appropriate.
*/
char **buildargv (char* string_input, int* argc);

/*

NAME

	freeargv -- free an argument vector

SYNOPSIS

	void freeargv (char** vector)

DESCRIPTION

	Free an argument vector that was built using buildargv.  Simply scans
	through the vector, freeing the memory for each argument until the
	terminating NULL is found, and then frees the vector itself.

RETURNS

	No value.

*/

void free_arg_vector (char** vector);
/*Free a null terminated char**, such as argv or argp*/

char** get_argp_appended(char** additonal_argument);
/*Return a new vector the current envp appended with additonal_argument. additonal_argument must be a null terminated char** */


size_t get_vector_count(char** vector);
/*Return he number of vector member. Vector must be a null terminated char**, such as argv or argp */

#define UNBUFFERED "0"
#define LINE_BUFFERED "L"
#define FULLY_BUFFERED "B"
#define DEFAULT_BUFFERING NULL
char** build_argp_stdbuf_env(char* mode[3]);
/*This return the argp you need to give to exceve in order to execute child with different buffering than default. The mode is an array that represent stdin (index 0), stdout (index 1), stderr (index2), each of this values can be set to UNBUFFERED, LINE_BUFFERED, FULLY_BUFFERED or any int (as a string) wich is equivalent to FULLY_BUFFERED with a custom size. watch out for collision with ascii character. If mode=DEFAULT_BUFFERING, then dont touch it. Example: 
 * char* mode[]={LINE_BUFFERED,DEFAULT_BUFFERING,UNBUFFERED}
 *
 * If stdbuf.so is not found (install coreutil?), it return NULL 
 * */ 

