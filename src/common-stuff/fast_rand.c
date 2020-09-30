//This code come from wikipédia lehmer generator
#include "fast_rand.h"
#include <stdlib.h>//rand
#include <time.h>//time
static uint32_t state=1;

uint32_t fast_rand_random_seed(){
	uint32_t seed= time(NULL);
	seed *= rand();
	seed %= 0x7fffffff;
	fast_rand_seed(seed);
	return seed;
}

void fast_rand_seed(uint32_t seed) {
	state=seed;
}

uint32_t fast_rand() {
	uint64_t product = (uint64_t)state * 48271;
	uint32_t x = (product & 0x7fffffff) + (product >> 31);

	x = (x & 0x7fffffff) + (x >> 31);
	return state = x;
}

uint32_t fast_rand_range(uint32_t interval){
	return fast_rand() % interval;
}



