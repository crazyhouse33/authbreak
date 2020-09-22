#include <stddef.h> //size_t
#include <stdio.h>//FIle
/*Define somes functions that should be standard*/
ssize_t read_append(int fd, char** buffer, size_t* string_size, size_t* buffer_max_size);
/*Read content of fd into buffer + string size. manage his size to never_get an overflow, side effect to actualize size and max size of buffer. Return read final status (0 or error)*/




ssize_t getdelim_tok(char** buffer, size_t* buffer_size, int sep, FILE* fp);
/*Like getdelim but terminate all read delim by a \0 unstead*/
