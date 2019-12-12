#pragma once

#include <string>
#include <vector>
#include <mpi.h>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include "colorsequence.h"
#include "respondedguess.h"
#include "proposedguess.h"
namespace mpi = boost::mpi;

class GameMaster {
public:
  GameMaster(ColorSequence, mpi::communicator);
  const ColorSequence solution;
  const mpi::communicator world;
  
  static GameMaster with_random_solution(unsigned int, unsigned char, mpi::communicator);
  void run();
 private:
  RespondedGuess evaluate_guess(const ColorSequence&);
  void report_response(RespondedGuess response);
};
