#include "or_combined_classifier.h"
#include <stdlib.h>
// After coding the polymoprhysm stuff, I realized it's really not worth all of that complex switching. Keeping track of every instance of each separate structure is not more messy in my opinion, and
// remove every switching. I am going to try this aproach with maccro base polymorhpism unstead

bool or_combined_classifier_classify_output(Or_combined_classifier *classifier, Output *out) {
  for (size_t i = 0; i < classifier->num_groups; i++) {
    if (composed_classifier_classify_output(&classifier->groups[i], out))
      return true;
  }
  return false;
}

void or_combined_classifier_add(Or_combined_classifier *group_class, Composed_classifier *class) {
  group_class->groups = realloc(group_class->groups, (group_class->num_groups + 1) * sizeof(Composed_classifier));
  group_class->groups[group_class->num_groups] = *class;
  group_class->num_groups++;
}

Or_combined_classifier *or_combined_classifier_new() { return calloc(1, sizeof(Or_combined_classifier)); }
