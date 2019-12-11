#include "guess.h"

template<class Archive>
void Guess::serialize(Archive & ar, const unsigned int version) {
  ar & perfect;
  ar & color_only;
  ar & color_sequence;
}
