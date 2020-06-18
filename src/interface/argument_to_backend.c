#include "argument_to_backend.h"
#include "output_classifier_front.h"
// Offer function to prepare the backend in order to reflect user passed stuff in argument (this separate a maximum the cli parsing with the actual resulted backend, since argument passing is hard
// allready)


// we cannot really do a good handy Composed_classifier classifier, it would require knowing parsing before hand
Composed_classifier *arguments_to_composed_classifier(Arguments *args) {
	Composed_classifier *classifier=composed_classifier_new(); 

	// we parse and control memory for the next round that we have enought place
	for (size_t i = 0; i < args->sucess_cpt; i++) {
		Authorized_classifier_type_key type = parse_classifier_str(classifier, args->sucess[i]);
	}
	return classifier;
}
