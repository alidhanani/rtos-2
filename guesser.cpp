#include "guesser.h"

Guesser::Guesser(unsigned int id, unsigned int number_nodes,
                 unsigned char number_colors, unsigned int number_spaces)
  :id(id), number_nodes(number_nodes), previous_guesses(std::vector<RespondedGuess>()),
   number_colors(number_colors), number_spaces(number_spaces), current_guess(get_first_guess(id, number_spaces, number_colors)) {}

std::optional<ColorSequence> Guesser::get_first_guess(unsigned int id, unsigned int number_spaces, unsigned char number_colors) {
  ColorSequence zero {number_colors, std::vector<unsigned char>(number_spaces, 0)};
  return zero + id;
}

void Guesser::report_guess(const RespondedGuess guess) {
  previous_guesses.push_back(guess);
}

int Guesser::guess_number() {
  return previous_guesses.size();
}

bool Guesser::is_plausible_guess(const ColorSequence& proposed_guess) {
  for (const RespondedGuess& guess : previous_guesses) {
    if (!is_plausible_guess(guess, proposed_guess)) {
      return false;
    }
  }
  return true;
}

bool Guesser::is_plausible_guess(const RespondedGuess& guess, const ColorSequence& proposed_guess) {
  util::response response = ColorSequence::compare(guess.color_sequence, proposed_guess);
  return response.perfect == guess.perfect
    && response.color_only == guess.color_only;
}
