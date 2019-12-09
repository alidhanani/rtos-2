#include "colorsequence.h"

ColorSequence::ColorSequence(unsigned char number_colors, std::vector<unsigned char> seq)
  :seq(seq), number_colors(number_colors) {}

std::optional<ColorSequence> ColorSequence::operator+(unsigned int incr) {
  std::vector<unsigned char> new_seq(seq.size());
  unsigned char carry = 0;
  
  for (unsigned int i = 0; i < seq.size(); i++) {
    unsigned char rem = static_cast<unsigned char>(incr % number_colors);
    incr -= rem;
    incr /= number_colors;
    int new_value = carry + rem + seq[i];
    if (new_value >= number_colors) {
      new_seq[i] = static_cast<unsigned char>(new_value % number_colors);
      carry = new_value / number_colors;
    } else {
      new_seq[i] = static_cast<unsigned char>(new_value);
      carry = 0;
    }
  }

  if (carry != 0) {
    return {};
  }
  return ColorSequence {number_colors, new_seq};
}
