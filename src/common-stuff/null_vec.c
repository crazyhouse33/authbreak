#include "null_vec.h"
#include <stdlib.h> //malloc
#include <string.h> //memcpy

/*Array based vector. Good enought for stable arrays*/

void free_vector(void **vector) {
  while (*vector != NULL)
    free(*vector);
  free(vector);
}

size_t get_vector_count(void **vector) {
  size_t argc = 0;
  while (vector[argc++] != NULL)
    ;
  return argc - 1;
}

void **create_vector(size_t size) {
  void **res = malloc(sizeof(void *) * (size + 1));
  res[size] = NULL;
  return res;
}

void **dup_vector(void **vec) {
  size_t size = get_vector_count(vec);
  void **res = create_vector(size);
  memcpy(res, vec, (size + 1) * sizeof(void *));
  return res;
}

size_t concatenate_vector(void ***vec1, void **vec2) {
  size_t size_1 = get_vector_count(*vec1);
  size_t size_2 = get_vector_count(vec2);
  size_t new_size = size_1 + size_2;
  *vec1 = realloc(*vec1, sizeof(void *) * (new_size + 1));
  memcpy((*vec1 + size_1), vec2, (size_2 + 1) * sizeof(void *));
  return new_size;
}

size_t put_vector(void ***vec, void *element) {
  size_t old_size = get_vector_count(*vec);
  *vec = realloc(*vec, sizeof(void *) * (old_size + 2));
  (*vec)[old_size] = element;
  (*vec)[old_size + 1] = NULL;
  return old_size + 1;
}

void **concatenation_vector(void **vec1, void **vec2) {
  void **vec1_clone = dup_vector(vec1);
  concatenate_vector(&vec1_clone, vec2);
  return vec1_clone;
}
