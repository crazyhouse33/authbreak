#include "dynamic_array.h"
#include <stdint.h>
#include <stdlib.h> //realloc
#include <sys/types.h>
#include "fast_rand.h"

static uint64_t next_power_2(uint64_t v) {
  v |= v >> 1;
  v |= v >> 2;
  v |= v >> 4;
  v |= v >> 8;
  v |= v >> 16;
  v++;
  return v;
}

Dynamic_Array *new_dynamic_array(size_t size) {
  size = next_power_2(size);
  Dynamic_Array *array = malloc(sizeof(Dynamic_Array));
  array->array = malloc(sizeof(void *) * size);
  array->size = size;
  return array;
}

void dynamic_array_put(Dynamic_Array *array, void *to_put, size_t where) {
  while (where > array->size - 1)
    array->size *= 4;

  array->array = realloc(array->array, sizeof(void *) * array->size);

  array->array[where] = to_put;
}

Dynamic_Array* as_dynamic_array(void**array);
void dynamic_array_shake(Dynamic_Array* array){
	for (size_t i=0; i < array->size; i++){
		size_t rand = fast_rand_until(array->size);
		void* randelem = array->array[rand];
		array->array[rand] = array->array[i];
		array->array[i]= randelem; 
	}
}

