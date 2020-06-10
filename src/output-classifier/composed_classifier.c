#include "composed_classifier.h"
#include "classifier_common.h"



#define CLASSIFY(type)                                                                                                                                                                                 \
  for (int i = 0; i < classifier->num_##type; i++)                                                                                                                                                     \
    if (!Classifier_##type##_classify(&classifier->type##_class[i], out))                                                                                                                              \
  return false;



bool classify_output(Composed_classifier *classifier, Output *out) {
  CLASSIFY(stringcmp);
  CLASSIFY(time);
  return classifier->num_stringcmp!=0 || classifier->num_time !=0;//if there where no classifier in the first place, it's counted as fail
}
