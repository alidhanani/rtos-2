#include <vector>
#include "colorsequence.h"

struct guess {
  const ColorSequence color_sequence;
  const util::response r;
};

class Guesser {
 public:
  void report_guess(const guess);
  Guesser(unsigned int,unsigned int, unsigned char, unsigned int); 
 private:
  const unsigned int id;
  const unsigned int number_nodes;
  std::vector<guess> previous_guesses;
  const unsigned char number_colors;
  const unsigned int number_spaces;
  bool is_plausible_guess(const ColorSequence&);
  bool is_plausible_guess(const guess&, const ColorSequence&);
};
