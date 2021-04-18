#include "geometric.h"
#include <math.h>

//https://en.wikipedia.org/wiki/Geometric_series
double geometric_n(double a, double r, size_t n){
	if (r==1)
		return a*n;
	double num= a *(1-pow(r,  n+1));
	double div= 1-r;
	return num/div;
}

// return Ux + Ux+1 + Ux+2 + ... Uy
double geometric_xtoy(double a, double r, size_t x, size_t y){
	size_t ret=geometric_n(a,r,y);
	if (x==0)
		return ret;
	return ret - geometric_n(a,r,x-1);

}

