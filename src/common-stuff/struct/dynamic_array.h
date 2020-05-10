#include <stddef.h>
//we suffer in perf from the the deferencing, in rust, you can declare a type that can vary in size
typedef struct Dynamic_Array
{
	  void** array;
	  size_t max_index;
} Dynamic_Array;

Dynamic_Array* new_dynamic_array(size_t size);

void dynamic_array_put(Dynamic_Array* array, void* to_put, size_t where);
