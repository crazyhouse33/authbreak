#include "fast_rand.h"
#include "munit.h"


void test_intervalle(unsigned int range){
	unsigned int a;
	for (int i=0; i<1000;i++){
		a=fast_rand_until(range);
		munit_assert_uint(a,<,range);
	}
}

int main() {
 test_intervalle(10000);
;//should work without memory bug

 fast_rand_seed(3);
 test_intervalle(2);
 test_intervalle(1);
 test_intervalle(10000);
 fast_rand_random_seed();
 test_intervalle(2);
 test_intervalle(1);
 test_intervalle(10000);
 return 0;
}
