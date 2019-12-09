#include <string>
#include <vector>
#include "util.h"

class GameMaster {
public:
  static GameMaster with_random_solution(unsigned int, unsigned char);
  GameMaster(util::color_seq,unsigned int);
  std::string pretty_print_solution();
  util::response evaluate_guess(const util::color_seq&);
 private:
  const util::color_seq solution;
  const unsigned int num_colors;
};
