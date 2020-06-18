#include <stdbool.h>
#include <sys/types.h>//ssize_t
size_t common_substring_size(char* string1, char* sting2,size_t max);
//scan string1 and string 2 trought at max max character and return the number of char they have in common until max.

#define SEARCH_ERROR_NO_MATCH -2
#define SEARCH_ERROR_MATCHS_AMBIGUITY -1

ssize_t get_unique_matching_string(char** list, char* string, size_t until);
/* list is a null terminated vector,
 * until is the size of the considered string for the algorythm (with or without \0) 
 * return the index of the only string that can possibily match among the string within list. 
  * */
ssize_t get_unique_matching_string_tolerant(char **list, char *string, size_t until, char** end_valid);
/*Same as on top but allow garbage after a match and make the given pointer point to the last valid letter
 *
 *For exemple, if list is: 
 * "tata"
 * "toto"
 *
 * then "tataplo" match tata and end point to to the A of tatAplo
 * This is used for exemple if you know that following stuff to parse can be 2 or 1 character, you just give two as until and let the algo return the best match, and give you the end of the valid match
 *
 * */
bool is_escaped(char *a_char, char escaper); 
/*Return true if character is preceded by the non escaped escaper*/

char *memchr_not_escaped(char *bloc, char to_found, size_t until, char escaper);
/*Return the next non escaped character*/


long int parse_int_intolerant(char *int_str, int error_status,char* error_format);
/*Parse a string as an int and fail with error give error_format (feeded by the the int_str) and given exit_status*/

unsigned long int parse_positive_int_intolerant(char *int_str, int error_status,char* error_format);
/*Same but dont accept negative values*/
