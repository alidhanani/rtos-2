#include "proposedguess.h"

template<class Archive>
void ProposedGuess::serialize(Archive & ar, const unsigned int version) {
  ar & guess_number;
  ar & color_sequence;
}
