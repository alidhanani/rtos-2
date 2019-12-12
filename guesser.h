#pragma once

#include <vector>
#include <mpi.h>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include "colorsequence.h"
#include "respondedguess.h"
#include "proposedguess.h"
namespace mpi = boost::mpi;

class Guesser {
 public:
  Guesser(mpi::communicator, unsigned int,unsigned int, unsigned char, unsigned int);
  
  void run();
 private:
  const mpi::communicator world;
  const unsigned int id;
  const unsigned int number_nodes;
  std::vector<RespondedGuess> previous_guesses;
  const unsigned char number_colors;
  const unsigned int number_spaces;
  std::optional<ColorSequence> current_guess;

  void report_guess(const RespondedGuess);
  int guess_number();
  bool is_plausible_guess(const ColorSequence&);
  bool is_plausible_guess(const RespondedGuess&, const ColorSequence&);
  static std::optional<ColorSequence> get_first_guess(unsigned int, unsigned int, unsigned char);
};
