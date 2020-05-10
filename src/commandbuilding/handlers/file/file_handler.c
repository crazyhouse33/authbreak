#include "handler.h" //Handler
#include "myread.h"  //getdelim_tok
#include "stdio.h"   //File pointer

#define UNLIKELY(x) __builtin_expect((x), 0)

/*Should we pass some options used only by some handlers into specials needs? this would unalign handler arrays (is it even possible?)*/

char *buffer = NULL;
size_t buffer_size = 0;

char *file_handler_next(Handler *handler) {
  FILE *fp = (FILE *)handler->special_needs;
  char sep = handler->options.separator;
  // TODO We use getdelim because we are lazy, but actually, it's annoying that it put the \0 after the delim and not replace, it use copy where we could use poiter, it does not manage end of file
  // annoying EOF removal (wich lead to need to call feof() for reach line and force to call. So replace that by a smarter buffer that check for eof at end of buffering once for us, and directely
  // change the buffer and point to the good parts. Actually this wont work with many handlers

  ssize_t res = getdelim(&buffer, &buffer_size, sep, fp);
  if (UNLIKELY(feof(fp))) { // We tell compiler it's unlikely so he is free to reorder the ifs. My guess is that it would fail to detect that file have more chances to be non empty that empty. I may
                            // be wrong tho and in that case it's still harmless
    rewind(fp);
    return NULL; // Signaling we are done
  } else if (buffer[res - 1] == sep)
    buffer[res - 1] = 0;
  return buffer;
}

void file_handler_init_special_needs(Handler *handler) { handler->special_needs = fopen(handler->main_component, "r"); }

char *file_handler_get_current(Handler *handler) { return file_handler_next(handler); }

void file_handler_free_needs(Handler *handler) { fclose(handler->special_needs); }
