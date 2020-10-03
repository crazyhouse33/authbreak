//This code come from wikipédia lehmer generator + https://www.pcg-random.org/posts/bounded-rands.html + https://en.wikipedia.org/wiki/Linear_congruential_generator
//For improvement check the following amazing prng https://github.com/espadrine/shishua
#include "fast_rand.h"
#include <stdlib.h>//rand
#include <time.h>//time

//2**32
#define MODULUS 0x100000000
static uint32_t state=1;

uint32_t fast_rand_random_seed(){
	uint32_t seed= time(NULL);
	seed *= rand();
	seed %= MODULUS;
	seed|=1;//Need odd seed with such MODULUS
	fast_rand_seed(seed);
	return seed;
}

void fast_rand_seed(uint32_t seed) {
	state=seed;
}

uint32_t fast_rand() {//ASSUME MODULUS 2**n
	uint64_t product = (uint64_t)state * 48271;
	uint32_t x = (product & (MODULUS-1)); 
	return state = x;
}

static uint32_t map_to_interval( uint32_t number, uint32_t interval){//x->[0:interval[  ASSUME RNG CAN GO TO 2**32
	uint64_t m = (uint64_t)number*(uint64_t)interval;
	return m >>32;
}

uint32_t fast_rand_range(uint32_t interval){
	return map_to_interval(fast_rand(), interval);
}



