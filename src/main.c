#include "interface/cliparser.h"
#include <argp.h> //no_help

int main(int argc, char *argv[]) {
	Arguments* argument=get_arguments(argc, argv,0);
	argument->no_timing=0;
}



