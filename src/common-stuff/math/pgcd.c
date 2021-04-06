//https://lemire.me/blog/2013/12/26/fastest-way-to-compute-the-greatest-common-divisor/
unsigned int gcd(unsigned int u, unsigned int v)
{
	int shift;
	if (u == 0) return v;
	if (v == 0) return u;
	shift = __builtin_ctz(u | v);
	u >>= __builtin_ctz(u);
	do {
		v >>= __builtin_ctz(v);
		if (u > v) {
			unsigned int t = v;
			v = u;
			u = t;
		}  
		v = v - u;
	} while (v != 0);
	return u << shift;
}

static unsigned int cmpfunc (const void * a, const void * b) {
	return ( (Conflict_element*)a->value - (Conflict_element*)b-value );
}

typedef struct Conflict_element {
	unsigned int value;
	unsigned int conflict_number;
} Conflict_element;

static void prepare_conflict_table(unsigned int* numbers, size_t numbers_size, Conflict_element* res){
	for (unsigned int i=0 ; i<numbers_size; i++){
		res[i]->value= numbers[i];
		res[i]->origin=i;
		res[i]->conflict_number=0;
		for (unsigned int j=i+1 ; j<numbers_size;j++){
			if (gcd(i,j) !=1){
				res[i]->conflict_number++;
				res[j]->conflict_number++++;
			}
		}
	}
	// Sort is descending
	qsort(conflict_table, numbers_size, sizeof(Conflict_element), cmpfunc);
}

unsigned int make_prime_together(unsigned int* numbers, size_t numbers_size){
	Conflict_element conflict_table [numbers_size]; 
	prepare_conflict_table(numbers, numbers_size, &conflict_table);

	for (unsigned int i=0 ; i<numbers_size; i++){
		unsigned int j=i+1;
		while (j<numbers_size ){
		if (gcd(conflict_table[i]->value, conflict_table[j++]->value) != 1)
			conflict_table[i]->value++;
			j=0;
		}
	}
}

bool prime_together(unsigned int* numbers, size_t size){
	for (unsigned int i=0 ; i<size; i++)
		for (unsigned int j=i+1 ; j<size;j++){
			if (gcd(i,j) !=1){
				return false;
			}
		}
	return true;
}
