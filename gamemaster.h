#pragma once

#include <string>
#include <vector>
#include <mpi.h>
#include <boost/mpi/collectives.hpp>
#include "colorsequence.h"
#include "respondedguess.h"
namespace mpi = boost::mpi;

class GameMaster {
public:
  GameMaster(ColorSequence, mpi::communicator);
  const ColorSequence solution;
  const mpi::communicator world;
  
  static GameMaster with_random_solution(unsigned int, unsigned char, mpi::communicator);
  RespondedGuess evaluate_guess(const ColorSequence&);
 private:
};
