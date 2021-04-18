#include <stdbool.h>
#include <stddef.h>
size_t gcd(size_t u, size_t v);
//compute gcd of two numbers

size_t make_prime_together(size_t* numbers, size_t size);
//take a list of number and try to make them prime one to each other with minimimum modification

bool prime_together(size_t* numbers, size_t size);
//Return true if numbers are prime on toward each other

