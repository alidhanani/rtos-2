#pragma once

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <vector>
#include <initializer_list>
#include <iterator>
#include <optional>
#include <stdexcept>
#include <string>
#include "util.h"

class ColorSequence {
 public:
  ColorSequence(unsigned char, std::vector<unsigned char>);
  std::optional<ColorSequence> operator+(unsigned int);
  std::vector<unsigned char> seq;
  unsigned char number_colors;
  std::string pretty_print() const;
  static util::response compare(const ColorSequence&, const ColorSequence&);
 private:
  friend class boost::serialization::access;
  template<class Archive> void serialize(Archive &, const unsigned int);
};
