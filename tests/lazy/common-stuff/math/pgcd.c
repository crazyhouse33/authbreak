#include "fast_rand.h"
#include "pgcd.h"
#include "munit.h"


void test_pgcd(unsigned int a, unsigned int b, unsigned int expected){
	munit_assert_true(gcd(a,b)==expected);
	munit_assert_true(gcd(b,a)==expected);
}

void test_prime_together(unsigned int* numbers, unsigned int size, bool expected){
	bool res=prime_together(numbers, size);
	munit_assert_true(res == expected);
}

void test_make_prime(unsigned int* numbers, unsigned int size){

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

	unsigned int test1[]={21,3,7};
	test_prime_together(test1, 3, false);
	test_make_prime(test1,3);

	unsigned int expected[] ={22,3,7};
	munit_assert_memory_equal(3*sizeof(unsigned int),test1,expected);


	unsigned int test3[]={7,3,21};
	test_prime_together(test3, 3, false);
	test_make_prime(test3,3);
	unsigned int expected3[] ={7,3,22};
	munit_assert_memory_equal(3*sizeof(unsigned int),test3,expected3);

	unsigned int test2[]={};
	test_prime_together(test2, 0, true);
	test_make_prime(test2,0);

	unsigned int test4[]={7,3,10};
	test_prime_together(test4, 3, true);
	test_make_prime(test4,3);
	unsigned int expected2[]={7,3,10};
	munit_assert_memory_equal(3*sizeof(unsigned int),test4,expected2);

	unsigned int test5[]={7,3,8,48,64,54,47,47,32,57,10};
	size_t size= (size_t) sizeof(test5)/sizeof(unsigned int);
	test_prime_together(test5, size, false);
	test_make_prime(test5,size);
	return 0;
}
