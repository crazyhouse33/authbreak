
#include "myfile.h"
#include <stdio.h>

bool is_openable_file(char* path){
	FILE *fp = fopen(path,"r");
	if( fp ) {
		// exists
		fclose(fp);
		return true;
	} 

	return false;
}
