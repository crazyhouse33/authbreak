#include "math.h"
int facto(int a) {
  int i = 1;
  while (a > 0)
    i *= a--;
  return i;
}

int k_among_n(int k, int n) { return facto(n) / (facto(k) * facto(n - k)); }

int my_pow(int a, int b) { // avoid lininking math just for that
  int res = 1;
  for (int i = 0; i < b; i++)
    res *= a;
  return res;
}
