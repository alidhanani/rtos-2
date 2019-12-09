#include "gamemaster.h"

struct guess {
  std::vector<unsigned char> color_sequence;
  response r;
};

class Guesser {
 public:
  void report_guess(guess);
  Guesser(unsigned int,unsigned int); 
 private:
  unsigned int id;
  unsigned int number_nodes;
  std::vector<guess> previous_guesses;
  bool is_plausible_guess(std::vector<unsigned char>);
};
