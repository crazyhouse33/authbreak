#include <math.h>
#include "base.h"
//https://stackoverflow.com/questions/1847131/how-many-digits-in-this-base
//Idk why log10 seems faster than log2
int digits_size(size_t n, size_t base)
{
	if (n==0)
		return 1;
	int s = (int)(log10((double)n)/log10((double)base)) + 1;
	return s;
}
