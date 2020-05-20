#include "dynamic_array.h"
#include <stdint.h>
#include <stdlib.h> //realloc
#include <sys/types.h>
// we suffer in perf from the the deferencing, in rust, you can declare a type that can vary in size. In C there is no way around this. If you want efficient acces you stick to an iteration that keep
// memory size in mind. This using this structure is way easier obviously and you should use it where performance dont matter

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
}

void dynamic_array_put(Dynamic_Array *array, void *to_put, size_t where) {
  while (where > array->size - 1)
    array->size *= 4;

  array->array = realloc(array->array, sizeof(void *) * array->size);

  array->array[where] = to_put;
}
