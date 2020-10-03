
#include "munit.h"
#include "delayer.h"
#include "time.h"

void basic_test(Delayer *rate) {
  unsigned int a;
  unsigned max = rate->min + rate->rand;
  for (int i = 0; i < 1000; i++) {
    a = _Delayer_delay_dry(rate);
    munit_assert_uint(a, <=, max);
    munit_assert_uint(a, >=, rate->min);
  }
}

void unity_test() {
  Delayer *r3 = Delayer_new(1, 0.001); // Should wait approx one sec
  unsigned long t1 = time(NULL);
  Delayer_delay(r3);
  unsigned long t2 = time(NULL);
  munit_assert_ulong(t2 - t1, <=, 2);
  munit_assert_ulong(t2 - t1, >=, 1);
}

int main() {
  Delayer *r1 = Delayer_new(1, 2);
  basic_test(r1);

  Delayer *r2 = Delayer_new(0, 2);
  basic_test(r2);

  Delayer *r3 = Delayer_new(2, 0);
  basic_test(r3);

  Delayer *r4 = Delayer_new(0, 0);
  basic_test(r4);

  unity_test();

  return 0;
}
