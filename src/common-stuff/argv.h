
/*This module provide functions to work with entry variable of process, such as argv and arp*/

#include <stdlib.h> 
#include <string.h>
#include <ctype.h>


/*
NAME

	buildargv -- build an argument vector from a string

SYNOPSIS

	char **arg_vector_from_string (char* string, size_t* argc)

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

	Store resulted argc in given argc

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
char **arg_vector_from_string (char* string_input, size_t* argc);

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

char** get_current_envp();
/*Return current envp*/

char** get_current_envp_appended(char** additonal_argument);
/*Return a new vector the current envp appended with additonal_argument. additonal_argument must be a null terminated char** */





#define UNBUFFERED "0"
#define LINE_BUFFERED "L"
#define DEFAULT_BUFFERING NULL

#ifndef LIBSTDBUF_PATH
#warning "libstdbuf is not found, build_stdbuf_exec_envp return the current envp, any use in execvpe wor as an execvp call"
#define LIBSTDBUF_PATH "ERROR-NOT-FOUND"
#define LIBSTDBUF_IS_FOUND 0
#else
#define LIBSTDBUF_IS_FOUND 1
#endif

char** build_stdbuf_exec_envp(char** mode);
/*This return the argp you need to give to exceve in order to execute child with different buffering than default. The mode is an array that represent stdin (index 0), stdout (index 1), stderr (index2), each of this values can be set to UNBUFFERED, LINE_BUFFERED or any int (as a string), which set the buffer size to be equal to this int. A good choice if you use pipe is "65536". There is not easy crossplatform way to return the default pipe size. If mode=DEFAULT_BUFFERING, then the buffering is managed as if you did not use this function . Example: 
 * char* mode[]={LINE_BUFFERED,DEFAULT_BUFFERING,UNBUFFERED}
 * 
 *
 * If stdbuf location had not be set at compile time in LIBSTDBUF_PATH is not found it return current envp.
 * (see stdbuf man page to see limitations of this function)
 * */ 


char* envp_get_value(char** envp, char* string);
/*This function is used Retrieve the part after the first "=" of the key variable of envp. Return null if not found */

size_t merge_envp(char*** envp1, char** envp2, char** key_to_merge_vec, char* separator);
//WARNING key_to_merge_vec is a null terminated char**
/*Merge envp1 and envp2. Return size of resulted vector. This concatenate env variable of envp2 into envp1, except if the variable is equal to one of the key_to_merge index. , in that case we do not simply concatenate but unstead append the value preceded by the given separator to the same variable in envp1. 
 *
 * This function is intented to manage conflict between differents options
 * Imagine you want to control buffering of the child while preloading one of the library.
 * If you just concatenate build_stdbuf_exec_envp(mode) and {"LDPRELOAD=yourlibrary",NULL} and give it to execve, then according to the execve implementation, one of the LDPRELOAD only is gonna be taken into account.
 * The solution to this problem is to use merge_envp(env1,env2,["LDPRELOAD"], ";")
 * */


char** get_envp_merged(char** envp1, char** envp2, char** key_to_merge, char* separator);
/*Same but work on a copy */
