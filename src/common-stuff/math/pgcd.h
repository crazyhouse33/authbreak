#include <stdbool.h>
#include <stddef.h>
unsigned int gcd(unsigned int u, unsigned int v);
//compute gcd of two numbers

unsigned int make_prime_together(unsigned int* numbers, size_t size);
//take a list of number and try to make them prime one to each other with minimimum modification

bool prime_together(unsigned int* numbers, size_t size);
//Return true if numbers are prime on toward each other

