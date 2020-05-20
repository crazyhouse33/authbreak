#include <stddef.h>//size_t
#include <stdbool.h>

bool is_openable_file(char* path);
/*Return true if path is a readable file. You can call perror if return false to check what happened*/

bool is_openable_file_until(char* path_begin, size_t until);/*Same but interpre only first char of path*/
