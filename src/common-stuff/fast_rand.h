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

uint32_t fast_rand_range(uint32_t interval);
/*Random number in between 0 included and interval excluded, interval must be > 0*/
