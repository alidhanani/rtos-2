#include "respondedguess.h"

RespondedGuess::RespondedGuess(unsigned int perfect, unsigned int color_only, ColorSequence color_sequence)
  :perfect(perfect), color_only(color_only), color_sequence(color_sequence) {}

RespondedGuess::RespondedGuess() {}

template<class Archive>
void RespondedGuess::serialize(Archive & ar, const unsigned int version) {
  ar & perfect;
  ar & color_only;
  ar & color_sequence;
}
