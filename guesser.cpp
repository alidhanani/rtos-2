#include "guesser.h"

Guesser::Guesser(unsigned int id, unsigned int number_nodes,
                 unsigned char number_colors, unsigned int number_spaces)
  :id(id), number_nodes(number_nodes), previous_guesses(std::vector<guess>()),
   number_colors(number_colors), number_spaces(number_spaces) {}

void Guesser::report_guess(const guess guess) {
  previous_guesses.push_back(guess);
}

bool Guesser::is_plausible_guess(const util::color_seq proposed_guess) {
  for (const guess guess : previous_guesses) {
    if (!is_plausible_guess(guess, proposed_guess)) {
      return false;
    }
  }
  return true;
}

bool Guesser::is_plausible_guess(const guess guess, const util::color_seq proposed_guess) {
  util::response response = util::compare_color_sequences(guess.color_sequence, proposed_guess, number_colors);
  return response.perfect == guess.r.perfect
    && response.color_only == guess.r.color_only;
}
