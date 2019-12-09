#include <string>
#include <vector>
#include "colorsequence.h"

class GameMaster {
public:
  static GameMaster with_random_solution(unsigned int, unsigned char);
  GameMaster(ColorSequence);
  std::string pretty_print_solution();
  util::response evaluate_guess(const ColorSequence&);
 private:
  const ColorSequence solution;
};
