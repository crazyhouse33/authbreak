#include "stdint.h"
/*fast random generator based on https://en.wikipedia.org/wiki/Lehmer_random_number_generator
Aimed to be really fast and not super random.  
*/
uint32_t fast_rand_random_seed();
/*Take a random time/system based seed, set state and return choosen seed*/

void fast_rand_seed(uint32_t seed);
/*Set new seed manually for random*/

uint32_t fast_rand();
/*Random 32 bits number*/

//TODO rename
uint32_t fast_rand_until(uint32_t until);
/*Random number in between 0 included and until excluded, until must be > 0*/
