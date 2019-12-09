#include "gamemaster.h"

struct guess {
  const std::vector<unsigned char> color_sequence;
  const response r;
};

class Guesser {
 public:
  // TODO: Rather than having all of the guessers use their own previous_guesses vec
  // they could simply all read from the same one
  void report_guess(const guess);
  Guesser(unsigned int,unsigned int, unsigned char, unsigned int); 
 private:
  const unsigned int id;
  const unsigned int number_nodes;
  std::vector<guess> previous_guesses;
  const unsigned char number_colors;
  const unsigned int number_spaces;
  bool is_plausible_guess(const std::vector<unsigned char>);
  bool is_plausible_guess(const guess, const std::vector<unsigned char>);
};
