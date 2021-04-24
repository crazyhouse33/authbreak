#include "error.h"
#include "handler.h" //Handler
#include "likely.h"
#include "myread.h" //getdelim_tok
#include <stdio.h>  //File pointer
#include "file_handler.h"


/*Should we pass some options used only by some handlers into specials needs? this would unalign handler arrays (is it even possible?)*/

char *buffer = NULL;
size_t buffer_size = 0;

char *file_handler_next(Handler *handler) {
  FILE *fp = ((File_needs*)handler->special_needs)->fp;
  char sep = handler->options.separator;
  // TODO We use getdelim because we are lazy, but actually, it's annoying that it put the \0 after the delim and not replace, it use copy where we could use poiter, it does not manage end of file
  // annoying EOF removal (wich lead to need to call feof() for reach line and force to call. So replace that by a smarter buffer that check for eof at end of buffering once for us, and directely
  // change the buffer and point to the good parts. Actually this wont work with many handlers

  ssize_t res = getdelim(&buffer, &buffer_size, sep, fp);
  if (UNLIKELY(feof(fp))) { // EOF reached
    if (res <= 0) {         // true end
      return NULL;                // Signaling we are done
    }
    if (buffer[res - 1] == '\n') { // On unix every file like to have a last \n, polluting the last guess
      buffer[res - 1] = 0;
      return buffer;
    }
  }
  if (buffer[res - 1] == sep) // getdelim dont replace sep at the end
    buffer[res - 1] = 0;
  return buffer;
}

void file_handler_reset_to(Handler* handler, size_t pos){
file_handler_reset( handler);
for (size_t i=0; i<pos;i++)
	file_handler_next(handler);
}

void file_handler_reset(Handler* handler){
FILE *fp = ((File_needs*)handler->special_needs)->fp;
rewind(fp);
}

void file_handler_init_special_needs(Handler *handler) {
	File_needs* needs = malloc(sizeof(File_needs));
	needs->fp = fopen(handler->main_component, "r");
	handler->special_needs=needs;
	if (needs->fp == NULL)
		controlled_error_msg(3, "Can not open file \"%s\"", handler->main_component);
}

void file_handler_free_needs(Handler *handler) { fclose(((File_needs*)handler->special_needs)->fp); }

size_t file_handler_size(Handler* handler){
	//Creating new handler with separated everything and just counting (slow)

	//dirty copy, do cleaner and pass it in handler
	Handler* copy = handler_new(handler->main_component, strlen(handler->main_component));
	copy->type=handler->type;
	copy->options=handler->options;

	char* current;
	size_t ret=0;
	while (current = file_handler_next(copy))
		ret++;
	handler_free(copy);

	return ret;

}

