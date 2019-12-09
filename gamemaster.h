#pragma once

#include <string>
#include <vector>
#include "colorsequence.h"

class GameMaster {
public:
  static GameMaster with_random_solution(unsigned int, unsigned char);
  GameMaster(ColorSequence);
  util::response evaluate_guess(const ColorSequence&);
  const ColorSequence solution;
 private:
};
