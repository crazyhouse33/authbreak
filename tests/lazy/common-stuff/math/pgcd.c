#include "fast_rand.h"
#include "pgcd.h"
#include "munit.h"


void test_pgcd(size_t a, size_t b, size_t expected){
	munit_assert_true(gcd(a,b)==expected);
	munit_assert_true(gcd(b,a)==expected);
}

void test_prime_together(size_t* numbers, size_t size, bool expected){
	bool res=prime_together(numbers, size);
	munit_assert_true(res == expected);
}

void test_make_prime(size_t* numbers, size_t size){

	make_prime_together(numbers, size);
	test_prime_together(numbers, size, true);
}


int main() {
	test_pgcd(42,63,21);
	test_pgcd(0,0,0);
	test_pgcd(8,0,8);
	test_pgcd(3,1,1);
	test_pgcd(8,8,8);
	// fibonnaci seq (31 and 32) (worst case)
	test_pgcd(1346269,2178309,1);

	size_t test1[]={21,3,7};
	test_prime_together(test1, 3, false);
	test_make_prime(test1,3);

	size_t expected[] ={22,3,7};
	munit_assert_memory_equal(3*sizeof(size_t),test1,expected);


	size_t test3[]={7,3,21};
	test_prime_together(test3, 3, false);
	test_make_prime(test3,3);
	size_t expected3[] ={7,3,22};
	munit_assert_memory_equal(3*sizeof(size_t),test3,expected3);

	size_t test2[]={};
	test_prime_together(test2, 0, true);
	test_make_prime(test2,0);

	size_t test4[]={7,3,10};
	test_prime_together(test4, 3, true);
	test_make_prime(test4,3);
	size_t expected2[]={7,3,10};
	munit_assert_memory_equal(3*sizeof(size_t),test4,expected2);

	size_t test5[]={7,3,8,48,64,54,47,47,32,57,10};
	size_t size= (size_t) sizeof(test5)/sizeof(size_t);
	test_prime_together(test5, size, false);
	test_make_prime(test5,size);
	return 0;
}
