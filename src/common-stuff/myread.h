#include <stddef.h> //size_t
#include <stdio.h>//FIle
/*Define somes functions that should be standard*/
size_t read_append(int fd, char** buffer, size_t* string_size, size_t* buffer_max_size);
/*Read content of fd into buffer and manage his size to never_get an overflow, side effect to actualize size and max size of buffer. Return the size of the new read data*/




ssize_t getdelim_tok(char** buffer, size_t* buffer_size, int sep, FILE* fp);
/*Like getdelim but terminate all read delim by a \0 unstead*/
