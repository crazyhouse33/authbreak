
#include "munit.h"
#include "rate_limiter.h"
#include "time.h"

void basic_test(Rate_limiter* rate){
	unsigned int a;
	unsigned max=rate->min+ rate->rand;
	for (int i=0; i<1000;i++){
		a= _Rate_limiter_limit_dry(rate);
		munit_assert_uint(a,<=,max);
		munit_assert_uint(a,>=,rate->min);
	}
}

void unity_test(){
	Rate_limiter* r3= Rate_limiter_new(1, 0.001);//Should wait approx one sec
	unsigned long t1=time(NULL);
	Rate_limiter_limit(r3);
	unsigned long t2=time(NULL);
	munit_assert_ulong(t2-t1,<=,2);
}

int main() {
	Rate_limiter* r1= Rate_limiter_new(1, 2);
	basic_test(r1);

	Rate_limiter* r2= Rate_limiter_new(0, 2);
	basic_test(r2);

	Rate_limiter* r3= Rate_limiter_new(2, 0);
	basic_test(r3);

	Rate_limiter* r4= Rate_limiter_new(0, 0);
	basic_test(r4);
	
	unity_test();



 return 0;
}
