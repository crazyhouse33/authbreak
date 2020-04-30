#include <stddef.h>
/*Some functions to concat some strings. Let you to choose performant or safe way, this is is not exaustif and I fill it according to my needs*/

size_t concat_string(char** string1, char* string2);
/*Concatenate directely string2 into string1, managing size safely if string are null terminated properly. Return the lenght of the result*/

size_t concat_string_fast_left(char** string1, char* string2, size_t s1);
/*Same buf just give the first size. The two functions are ment to be chained.
 *You start by concatenating with unkonw lenght string and you use the returned size in the subsequent call to concat_string_left.
 * */


size_t concat_string_fast(char** string1, char* string, size_t size_1, size_t size_2);
/*Same but trust your user input given size unstead of using strlen. This avoid the famous quadratic complexity using consecutive concatenation*/


char* get_concatenation_string(char* string1, char* string2);
/*Return the concatenation of the two strings, manage size*/


char* get_concatenation_string_fast(char* string1, char* string, size_t size_1, size_t size_2);
/*Same but trust your user input given size unstead of using strlen. This avoid the famous quadratic complexity using consecutive concatenation*/


size_t concat_string_cut(char** string1, char* string2, size_t s2_cut_len);
/* This concatenate the string1 with the string s2 cutted to be have len s2_cut_len), and add a null character in the end. You have to specify the size of the cut. 
 * */

size_t concat_char(char** string_1, char c);
/*Concatenate string_1 with the character c*/



