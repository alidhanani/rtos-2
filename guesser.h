#pragma once

#include <vector>
#include "colorsequence.h"
#include "respondedguess.h"

class Guesser {
 public:
  void report_guess(const RespondedGuess);
  Guesser(unsigned int,unsigned int, unsigned char, unsigned int);
  bool is_plausible_guess(const ColorSequence&);
  std::optional<ColorSequence> current_guess;
  int guess_number();
 private:
  const unsigned int id;
  const unsigned int number_nodes;
  std::vector<RespondedGuess> previous_guesses;
  const unsigned char number_colors;
  const unsigned int number_spaces;
  bool is_plausible_guess(const RespondedGuess&, const ColorSequence&);
  static std::optional<ColorSequence> get_first_guess(unsigned int, unsigned int, unsigned char);
};
