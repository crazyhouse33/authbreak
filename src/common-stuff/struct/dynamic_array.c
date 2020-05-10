#include "dynamic_array.h"
#include <stddef.h>
#include <stdlib.h> //realloc
// we suffer in perf from the the deferencing, in rust, you can declare a type that can vary in size. In C there is no way around this. If you want efficient acces you stick to an iteration that keep
// memory size in mind. This using this structure is way easier obviously and you should use it where performance dont matter

Dynamic_Array *new_dynamic_array(size_t size) {
  Dynamic_Array *array = malloc(sizeof(Dynamic_Array));
  array->array = malloc(sizeof(void *) * size);
  array->max_index = size - 1;
}

void dynamic_array_put(Dynamic_Array *array, void *to_put, size_t where) {
  if (where > array->max_index) {
    array->max_index *= 4;
    array->array = realloc(array->array, sizeof(void *) * array->max_index);
  }
  array->array[where] = to_put;
}
