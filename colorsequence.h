#pragma once

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <vector>
#include <initializer_list>
#include <iterator>
#include <optional>
#include <stdexcept>
#include <string>

struct response {
  unsigned int perfect;
  unsigned int color_only;
};

class ColorSequence {
 public:  ColorSequence(unsigned char, std::vector<unsigned char>);
  ColorSequence();
  std::optional<ColorSequence> operator+(unsigned int);
  std::vector<unsigned char> seq;
  unsigned char number_colors;
  std::string pretty_print() const;
  static response compare(const ColorSequence&, const ColorSequence&);
 private:
  friend class boost::serialization::access;
  template<class Archive> void serialize(Archive & ar, const unsigned int version) {
    ar & seq;
    ar & number_colors;
  };
};
