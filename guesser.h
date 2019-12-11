#pragma once

#include <vector>
#include "colorsequence.h"
#include "guess.h"

class Guesser {
 public:
  void report_guess(const Guess);
  Guesser(unsigned int,unsigned int, unsigned char, unsigned int);
  bool is_plausible_guess(const ColorSequence&);
  std::optional<ColorSequence> current_guess;
 private:
  const unsigned int id;
  const unsigned int number_nodes;
  std::vector<Guess> previous_guesses;
  const unsigned char number_colors;
  const unsigned int number_spaces;
  bool is_plausible_guess(const Guess&, const ColorSequence&);
  static std::optional<ColorSequence> get_first_guess(unsigned int, unsigned int, unsigned char);
};
