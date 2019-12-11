#pragma once

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "colorsequence.h"

class RespondedGuess {
 public:
  unsigned int perfect;
  unsigned int color_only;
  ColorSequence color_sequence;
 private:
  friend class boost::serialization::access;
  template<class Archive> void serialize(Archive &, const unsigned int);
};
