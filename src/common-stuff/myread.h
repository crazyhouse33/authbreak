#include <stddef.h> //size_t
size_t read_append(int fd, char** buffer, size_t* string_size, size_t* buffer_max_size);
/*Read content of fd into buffer and manage his size to never_get an overflow, side effect to actualize size and max size of buffer. Return the size of the new read data*/
