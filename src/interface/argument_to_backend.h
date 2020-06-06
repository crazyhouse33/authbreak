#include "cliparser.h"
#include "composed_classifier.h"
//Offer function to prepare the backend in order to reflect user passed stuff in argument (this separate a maximum the cli parsing with the actual resulted backend, since argument passing is hard allready)

Composed_classifier* arguments_to_composed_classifier(Arguments* args);
/*create a composed classifier reflecting given arguments*/
