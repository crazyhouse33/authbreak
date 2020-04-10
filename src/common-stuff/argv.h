
//This functions come for libiberty, wich I just integrated to the sources cause could build there stuff
//https://opensource.apple.com/source/gcc/gcc-926/libiberty/argv.c.auto.html

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

void freeargv (char** vector);
