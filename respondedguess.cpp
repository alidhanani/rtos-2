#include "respondedguess.h"

template<class Archive>
void RespondedGuess::serialize(Archive & ar, const unsigned int version) {
  ar & perfect;
  ar & color_only;
  ar & color_sequence;
}
