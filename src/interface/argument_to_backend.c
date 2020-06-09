#include "argument_to_backend.h"
#include "output_classifier_front.h"
// Offer function to prepare the backend in order to reflect user passed stuff in argument (this separate a maximum the cli parsing with the actual resulted backend, since argument passing is hard
// allready)

#define INIT(X)                                                                                                                                                                                        \
  size_t max_##X##_num = 8;                                                                                                                                                                            \
  classifier->X##_class = malloc(sizeof(Classifier_##X) * max_##X##_num)

#define CASE(X)                                                                                                                                                                                        \
  case X:                                                                                                                                                                                              \
    if (classifier->num_##X >= max_##X##_num) {                                                                                                                                                        \
      max_##X##_num << 1;                                                                                                                                                                              \
      classifier->X##_class = realloc(classifier->X##_class, max_##X##_num);                                                                                                                           \
    }                                                                                                                                                                                                  \
    break

Composed_classifier *arguments_to_composed_classifier(Arguments *args) {
  Composed_classifier *classifier = malloc(sizeof(Composed_classifier));

  INIT(stringcmp);
  INIT(time);

  // we parse and control memory for the next round that we have enought place
  for (size_t i = 0; i < args->sucess_cpt; i++) {
    Authorized_classifier_type_key type = parse_classifier_str(classifier, args->sucess[i]);
    switch (type) {
      CASE(stringcmp);
      CASE(time);
    }
  }
  return classifier;
}
