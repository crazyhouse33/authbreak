#include <stddef.h>//size_t
#include <stdbool.h>

bool is_openable_file(char* path);
/*Return true if path is a readable file. You can call perror if return false to check what happened*/

bool is_openable_file_until(char* path_begin, size_t until);/*Same but interpre only first char of path*/

char* search_in_path_openable_file(char* file_name);
/*Search into PATH env variable a file_name and return the full path of the first that is openable, NULL if not in path*/

char* search_executable(char* file_name);
/*Search file, if not openable and not absolute path(contain /), look for opennable file in the path. If nothing is openable, return NULL. If something is openable, return it as it is (not guaratented to have a full path, but garatanted to be openable)*/

