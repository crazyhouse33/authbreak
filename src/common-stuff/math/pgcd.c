#include <stddef.h>//size_t
#include <stdlib.h>//qsort
#include <strings.h>//bzero
#include "pgcd.h"


//https://lemire.me/blog/2013/12/26/fastest-way-to-compute-the-greatest-common-divisor/
size_t gcd(size_t u, size_t v)
{
	int shift;
	if (u == 0) return v;
	if (v == 0) return u;
	shift = __builtin_ctz(u | v);
	u >>= __builtin_ctz(u);
	do {
		v >>= __builtin_ctz(v);
		if (u > v) {
			size_t t = v;
			v = u;
			u = t;
		}  
		v = v - u;
	} while (v != 0);
	return u << shift;
}

typedef struct Conflict_element {
	size_t value;
	size_t origin;
	size_t conflict_number;
} Conflict_element;


static int cmpfunc ( const void * a, const void * b) {
	return ( ((Conflict_element*)b)->value - ((Conflict_element*)a)->value  );
}


static void prepare_conflict_table(size_t* numbers, size_t numbers_size, Conflict_element* res){
	bzero((void*) res, numbers_size * sizeof(Conflict_element));
	for (int i=0 ; i<numbers_size; i++){
		res[i].origin=i;
		res[i].value= numbers[i];
		for (int j=i+1 ; j<numbers_size;j++){
			if (gcd(numbers[i],numbers[j]) !=1){
				res[i].conflict_number++;
				res[j].conflict_number++;
			}
		}
	}
	// Sort is descending
	qsort(res, numbers_size, sizeof(Conflict_element), cmpfunc);
}

//Room for improvement. This algo is fast but sensible to bad input(eg 2 facto). Also it does not care to increment small value, which is bad for our use case
size_t make_prime_together(size_t* numbers, size_t numbers_size){
	Conflict_element conflict_table [numbers_size]; 
	prepare_conflict_table(numbers, numbers_size, conflict_table);

	for (int i=0 ; i<numbers_size; i++){
		int j=0;
		while (j<numbers_size ){
			if (j==i){
				j++;
				continue;
			}
			if (gcd(numbers[conflict_table[i].origin], numbers[conflict_table[j].origin]) != 1){
				numbers[conflict_table[i].origin]++;
				j=0;
			}
			else{
				j++;
			}
		}
	}
}

bool prime_together(size_t* numbers, size_t size){
	for (int i=0 ; i<size; i++)
		for (int j=i+1 ; j<size;j++){
			if (gcd(numbers[i],numbers[j]) !=1){
				return false;
			}
		}
	return true;
}
