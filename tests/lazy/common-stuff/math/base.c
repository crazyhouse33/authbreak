#include "base.h"
#include "munit.h"

void test_size(size_t a, size_t base, size_t expected){
	munit_assert_size(digits_size(a,base),==,expected);
}

int main() {
	test_size(21374823498, 10,11);
	test_size(1, 2,1);
	test_size(2, 2,2);
	test_size(3, 2,2);
	test_size(0, 2,1);
	return 0;
}
