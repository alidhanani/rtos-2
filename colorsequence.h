#include <vector>
#include <initializer_list>
#include <iterator>
#include <optional>
#include <stdexcept>
#include "util.h"

class ColorSequence {
 public:
  ColorSequence(unsigned char, std::vector<unsigned char>);
  std::optional<ColorSequence> operator+(unsigned int);
  const std::vector<unsigned char> seq;
  const unsigned char number_colors;
  static util::response compare(const ColorSequence&, const ColorSequence&);
 private:
};
