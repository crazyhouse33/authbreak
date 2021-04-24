#include <math.h>
//https://stackoverflow.com/questions/1847131/how-many-digits-in-this-base
int digits_size(size_t n, size_t base)
{
	    	int s = int(log10(1.0*n)/log10(1.0*base)) + 1;
		return s;
}
