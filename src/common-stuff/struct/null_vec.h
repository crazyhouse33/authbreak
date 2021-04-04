#include <stddef.h> //size_t

void** create_vector(size_t size);
/*Initialize memory for vector of size size*/

size_t get_vector_count(void** vector);
/*Return he number of vector member. Vector must be  null terminated */

void** dup_vector(void** vec);
/*Return a copy of a vector*/

size_t concatenate_vector(void*** vec1, void** vec2);
/*Concatenate vec1 with vec2, return the new size of vec1*/

size_t put_vector(void*** vec1, void* element);
/*Add element to the vector*/

void** concatenation_vector(void** vec1, void** vec2);
/*Return a copy of vec1 concatenated with vec2 */

void free_vector (void** vector);
/*Free a null terminated vector*/




 



