#pragma once

#include <string>
#include <vector>
#include "colorsequence.h"
#include "respondedguess.h"

class GameMaster {
public:
  static GameMaster with_random_solution(unsigned int, unsigned char);
  GameMaster(ColorSequence);
  RespondedGuess evaluate_guess(const ColorSequence&);
  const ColorSequence solution;
 private:
};
