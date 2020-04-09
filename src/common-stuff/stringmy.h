#include <string.h> //size_t
/*This module define trim, a (almost) no side effect function to remove white character at end/begining of string. It also define a lot of direct pointer maipulation. Thoses function are hard to use but save some operations if you dont care about modifying source string. Remember that in C litteral are not writable, wich mean you cannot pass char*="literal" values to in place functions. 
 */

void left_trim_in_place(char** string);
/*Make given pointer point on the first non white character*/

void right_trim_in_place(char** string_end);
	/*Add a null char just after first non white character on the left of the pointer and make it point to it*/
	
void trim_in_place(char** string_begin, char** string_end);
/*Make given pointer point on the first non white character, and add a null char just after the first non white character on the left of the end pointer*/

char* left_trim(char* string);
/* Return pointer pointing on the first non white character*/

char* point_to_last_white(char** string);
/*Make string_end point to the last white on the end of the string  */

char* trim(char* string_begin, char* string_end);
/* Trim. The only side effect is to moove string_end to the new string end. Which often will be the desired/dont care behaviour. Just be aware of it. */

char* get_after_sep_part(char* string, char sep, size_t until);
/*Return pointer to character after separator. Parse until the until value, if no separator is found return the initial pointer*/


