#include "composed_classifier.h"
#include "classifier_common.h"

#define CLASSIFY(type, name, to_classify)                                                                                                                                                              \
  for (int i = 0; i < classifier->num_##name; i++)                                                                                                                                                     \
    if (!classifier_##type##_classify(&classifier->name##_class[i], to_classify))                                                                                                                      \
      return false == classifier->target;

// TODO do a X maccro that call Classify on any type defined on the allready defined enum authorized classifier type , and construct the return statement, so no possible messup is ever possible (like
// forgetting one of those)
bool composed_classifier_classify_output(Composed_classifier *classifier, Output *out) {
  CLASSIFY(stringcmp, stringcmp, out->out);
  CLASSIFY(diff_long, time, out->term_time);
  CLASSIFY(diff_int, status_diff, out->exit_status);
  CLASSIFY(eq_int, status_eq, out->exit_status);
  return (classifier->num_stringcmp != 0 || classifier->num_time != 0 || classifier->num_status_diff != 0 || classifier->num_status_eq != 0) ==
         classifier->target; // if there where no classifier in the first place, it's counted as fail
}

Composed_classifier *composed_classifier_new(bool target) {
  Composed_classifier *classifier = calloc(1, sizeof(Composed_classifier));
  classifier->target = target;
  return classifier;
}
