#pragma once

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "colorsequence.h"

class ProposedGuess {
 public:
  unsigned int guess_number;
  ColorSequence color_sequence;
 private:
  friend class boost::serialization::access;
  template<class Archive> void serialize(Archive &, const unsigned int);
};
