#include <stddef.h>//size_t
#include <stdbool.h>
void assert_not_present(char *string, char **result, size_t size_res);

void assert_present(char *string, char **result, size_t size_res); 


void assert_is_permutation(char** res1, char**res2, size_t size1, size_t size2);

void assert_all_unique(char** res, size_t size);

char** generate_iteration_history(size_t* s, char* generate (int)); 
//call generate until get null and return the history, set s to size

char** assert_iteration_test(char *generate(int), size_t expected_cycle_size); //This test than history of generate is permutation-cyclique(the cycle 2 must be a permutation of 1) of order expected_cycle_size, and that the cycle is composed by uniq value. THis also return last history 

bool array_equal(char **res1, char **res2, size_t size);
