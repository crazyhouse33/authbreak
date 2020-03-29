#include "interface/cliparser.h"

/* main.c */
int main(int argc, char *argv[]) {
	Arguments* argument=get_arguments(argc, argv);
	argument->no_timing=0;
}



