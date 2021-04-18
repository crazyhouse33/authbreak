#include "file_info.h"
#include "stdlib.h" //malloc
#include <stdio.h>
#include <string.h> //strcpy

/*I wanted to do a really cross platform way. access or _acess may be better*/
bool is_openable_file(char *path) {
  FILE *fp = fopen(path, "r");
  if (fp) {
    // exists
    fclose(fp);
    return true;
  }

  return false;
}

bool is_openable_file_until(char *path_begin, size_t until) {
  char old = path_begin[until];
  path_begin[until] = 0;
  bool res = is_openable_file(path_begin);
  path_begin[until] = old;
  return res;
}

/*You may thinks that libc would have done this function and use it to implement execp function family, but you would be wrong. They just hardcoded the search in every execp function. Unbelievable.
 *
 * So this function is a modification of their messy function of execvp.
 *
 * */

char *search_in_path_openable_file(char *file) {
  char *path = getenv("PATH");
  if (path == NULL)
    return NULL;
  size_t pathlen = strlen(path);
  size_t len = strlen(file) + 1;
  int total_max_size = pathlen + len+1;
  char *buf = malloc(sizeof(char) * total_max_size);
  if (*file == '\0') {
    return NULL;
  }
  char *name, *p;
  /* Copy the file name at the top.  */
  name = memcpy(buf + pathlen + 1, file, len);
  /* And add the slash.  */
  *--name = '/';
  p = path;
  do {
    char *startp;
    path = p;
    // Let's avoid this GNU extension.
    // p = strchrnul (path, ':');
    p = strchr(path, ':');
    if (!p)
      p = strchr(path, '\0');
    if (p == path)
      /* Two adjacent colons, or a colon at the beginning or the end
         of `PATH' means to search the current directory.  */
      startp = name + 1;
    else
      startp = memcpy(name - (p - path), path, p - path);
    /* Try to execute this name.  If it works, execv will not return.  */
    if (is_openable_file(startp))
      return startp;
  } while (*p++ != '\0');
  /* We tried every element and none of them worked.  */
  return NULL;
}

char *search_executable(char *file_name) {

  if (is_openable_file(file_name)) { // See realpath manual bug. Watch out
    return file_name;
  }
  if (strchr(file_name, '/') != NULL) // Don't search when it contains a slash.
    return NULL;
  return search_in_path_openable_file(file_name);
}

