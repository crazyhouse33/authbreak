#include "geometric.h"
#include "munit.h"
#include "math.h"


void test_geom(double a, double r, size_t n, size_t expected){
	munit_assert_double(geometric_n(a,r,n), ==, expected);
}


void test_xtoy(double a, double r,  size_t x, size_t y, size_t expected){
	munit_assert_double(geometric_xtoy(a,r,x,y), ==, expected);
}

int main() {
	test_geom(46,0,3,46);
	test_geom(46,46,0,46);
	test_geom(46,3,1,46*4);
	test_geom(46,23,3,585120);
	// fibonnaci seq (31 and 32) (worst case)
	test_xtoy(3,21,0,46,geometric_n(3,21,46));
	test_xtoy(3,4,2,5,4080);
	test_xtoy(3,21,4,4, 3*pow(21,4));

	return 0;
}
