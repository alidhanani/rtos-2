#include "guesser.h"

Guesser::Guesser(unsigned int id, unsigned int number_nodes,
                 unsigned char number_colors, unsigned int number_spaces)
  :id(id), number_nodes(number_nodes), previous_guesses(std::vector<guess>()),
   number_colors(number_colors), number_spaces(number_spaces) {}

void Guesser::report_guess(const guess guess) {
  previous_guesses.push_back(guess);
}

bool Guesser::is_plausible_guess(const std::vector<unsigned char> proposed_guess) {
  for (const guess guess : previous_guesses) {
    if (!is_plausible_guess(guess, proposed_guess)) {
      return false;
    }
  }
  return true;
}

// TODO: Merge with GameMaster::evaluate_guess ?
bool Guesser::is_plausible_guess(const guess guess, const std::vector<unsigned char> proposed_guess) {
  int matching_perfect = 0;
  int matching_color_only = 0;
  std::vector<unsigned int> color_count_guess(number_colors, 0);
  std::vector<unsigned int> color_count_proposed_guess(number_colors, 0);
  for (unsigned int i = 0; i < proposed_guess.size(); i++) {
    if (proposed_guess[i] == guess.color_sequence[i]) {
      matching_perfect++;
    }
    color_count_guess[guess.color_sequence[i]]++;
    color_count_proposed_guess[proposed_guess[i]]++;
  }

  for (unsigned int i = 0; i < number_colors; i++) {
    matching_color_only += std::min(color_count_guess[i], color_count_proposed_guess[i]);
  }
  matching_color_only -= matching_perfect;

  return matching_perfect == guess.r.perfect
    && matching_color_only == guess.r.color_only;
}
