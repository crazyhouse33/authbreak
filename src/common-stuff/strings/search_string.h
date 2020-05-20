#include <stdbool.h>
#include <sys/types.h>//ssize_t
size_t first_diff(char* string1, char* sting2,size_t max);
//scan string1 and string 2 trought at max max character and return the first char on which they differ. If they dont differ before max, return max eventhought they may never differ

#define SEARCH_ERROR_NO_MATCH -2
#define SEARCH_ERROR_MATCHS_AMBIGUITY -1

ssize_t get_unique_matching_string(char** list, char* string, size_t until);
/* list is a null terminated vector,
 * until is the size of the considered string for the algorythm (with or without \0) 
 * return the index of the only string that can possibily match among the string within list. 
 *
 *
 * char** list={"separator", "septre", "bob",NULL}
 * get_uniq_matching_string(list, "sep", strlen("sep"));
 * return SEARCH_ERROR_MATCHS_AMBIGUITY
 * while
 * get_uniq_matching_string(list, "sepa", strlen("sep"));
 * return separator
 * */

bool is_escaped(char *a_char, char escaper); 
/*Return true if character is preceded by the non escaped escaper*/

char *memchr_not_escaped(char *bloc, char to_found, size_t until, char escaper);
/*Return the next non escaped character*/

