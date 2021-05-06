#include "handler.h"         //Handler
#include <sys/types.h>
#include <stdio.h>

typedef struct File_needs
{
	FILE* fp;
} File_needs;

char* file_handler_next(Handler* handler);
/*Return next string until delimiter, the buffering is managed by stdio.h. If eof, return NULL and reset file position to 0*/

void file_handler_init_special_needs(Handler* handler);
//Set special need to file pointer to the maincomponent interpreted as a path

void file_handler_free_needs(Handler* handler);

size_t file_handler_size(Handler* handler);

void file_handler_reset(Handler* handler);



