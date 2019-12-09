#include <string>
#include <vector>
#include "util.h"

class GameMaster {
 public:
  static GameMaster with_random_solution(unsigned int, unsigned char);
  GameMaster(std::vector<unsigned char>,unsigned int);
  std::string pretty_print_solution();
  util::response evaluate_guess(std::vector<unsigned char>);
 private:
  const std::vector<unsigned char> solution;
  const unsigned int num_colors;
};
