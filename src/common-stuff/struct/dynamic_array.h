#include <sys/types.h>
typedef struct Dynamic_Array
{
	  void** array;
	  size_t size;
} Dynamic_Array;

Dynamic_Array* new_dynamic_array(size_t size);

void dynamic_array_put(Dynamic_Array* array, void* to_put, size_t where);
void dynamic_array_shake(Dynamic_Array* array);
