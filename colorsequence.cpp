#include "colorsequence.h"

ColorSequence::ColorSequence(unsigned char number_colors, std::vector<unsigned char> seq)
  :seq(seq), number_colors(number_colors) {}

ColorSequence::ColorSequence() {}

// The color sequence can be considered a number in base n, where n is number_colors
// We can then perform addition with the standard algorithm
// (moving from least significant digit to most significant, and keeping track of the carry value)
std::optional<ColorSequence> ColorSequence::operator+(unsigned int incr) {
  std::vector<unsigned char> new_seq(seq.size());
  unsigned char carry = 0;
  
  for (unsigned int i = 0; i < seq.size(); i++) {
    unsigned char rem = static_cast<unsigned char>(incr % number_colors);
    incr -= rem;
    incr /= number_colors;

    // We calculate new_value in an int to avoid overflow
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
    // The result of the addition is unrepresentable with the number of spaces
    // It has overflowed the color sequence and so we return an empty optional
    return {};
  }
  return ColorSequence {number_colors, new_seq};
}

std::string ColorSequence::pretty_print() const {
  std::string solution_string;
  for (const unsigned char color : seq) {
    // We add 97 so that each color is represented by an ASCII letter
    // This way color 0 is printed as an 'a'
    solution_string += color + 97;
  }
  return solution_string;
}

response ColorSequence::compare(const ColorSequence& seq1, const ColorSequence& seq2) {
  if (seq1.seq.size() != seq2.seq.size()) {
    throw std::runtime_error("Cannot compare color sequences of different sizes");
  }

  if (seq1.number_colors != seq2.number_colors) {
    throw std::runtime_error("Cannot compare color sequences with different colors");
  }
  
  unsigned int perfect = 0;
  unsigned int color_only = 0;
  unsigned char num_colors = seq1.number_colors;
  unsigned int seq_length = seq1.seq.size();

  // To calculate color_only, we keep track of the frequency of colors in seq1 and seq2
  // The i^th index tracks the frequency of color i
  std::vector<unsigned int> color_count_seq1(num_colors, 0);
  std::vector<unsigned int> color_count_seq2(num_colors, 0);
  for (unsigned int i = 0; i < seq_length; i++) {
    if (seq1.seq[i] == seq2.seq[i]) {
      perfect++;
    }
    color_count_seq1[seq1.seq[i]]++;
    color_count_seq2[seq2.seq[i]]++;
  }
  
  for (unsigned int i = 0; i < num_colors; i++) {
    color_only += std::min(color_count_seq1[i], color_count_seq2[i]);
  }
  
  color_only -= perfect;
  return response {perfect, color_only}; 
}

