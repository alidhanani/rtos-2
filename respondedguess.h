#pragma once

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "colorsequence.h"

class RespondedGuess {
 public:
  RespondedGuess(unsigned int, unsigned int, ColorSequence);
  RespondedGuess();
  unsigned int perfect;
  unsigned int color_only;
  ColorSequence color_sequence;
  friend class boost::serialization::access;
  template<class Archive> void serialize(Archive & ar, const unsigned int version) {
    ar & perfect;
    ar & color_only;
    ar & color_sequence;
  };
private:
};
