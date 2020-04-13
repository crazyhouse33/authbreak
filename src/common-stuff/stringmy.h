#include <stddef.h> //size_t
/*This module define trim, a no side effect function to remove white character at end/begining of string. It also define a lot of direct pointer manipulation. Thoses function are hard to use but save some operations if you dont care about modifying source string. Remember that in C litteral are not writable, wich mean you cannot pass char*="literal" values to in place functions. 
 */

void left_trim_in_place(char** string);
/*Make given pointer point on the first non white character*/

void right_trim_in_place(char** string_end);
	/*Add a null char just after first non white character on the left of the pointer and make it point to it*/

char* right_trim(char* string_end);
/*Add a null character just after first non white character on the left of the pointer.*/
	
void trim_in_place(char** string_begin, char** string_end);
/*Make given pointer point on the first non white character, and add a null char just after the first non white character on the left of the end pointer. Make end pointer point to new end*/

char* trim_in_place_preserve_left(char* string, char** right);
/*Return pointer on the first non white character, and add a null char just after the first non white character on the left of the end pointer. Make end pointer point to new end. */

void trim_in_place_preserve_right(char** string, char* string_end);
/* Make string point on the first non white character, and add a null char just after the first non white character on the left of the end pointer. */

char* left_trim(char* string);
/* Return pointer pointing on the first non white character*/


char* get_pointer_to_last_white(char* string_end);
/*Return pointer to the last white on the end of the string*/

void point_to_last_white(char** string);
/*Make string_end point to the last white on the end of the string  */

char* trim(char* string_begin, char* string_end);
/*trim a string without side effect, return pointer to create string*/
char* trim_change_end(char* string_begin, char* string_end);
/* Trim with the side effect of moving string_end to the new string end.*/

char* get_after_sep_part(char* string, char sep, size_t until);
/*Return pointer to character after separator. Parse until the until value, if no separator is found return the initial pointer*/


