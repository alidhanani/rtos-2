#include <random>
#include <time.h>
#include <string>
#include "gamemaster.h"

GameMaster GameMaster::with_random_solution(unsigned int num_spaces, unsigned char num_colors, mpi::communicator world) {
  srand(time(0));
  std::vector<unsigned char> solution(num_spaces);
  for (unsigned int i = 0; i < num_spaces; i++) {
    solution[i] = rand() % num_colors;
  }
  return GameMaster {ColorSequence {num_colors, solution}, world};
}

GameMaster::GameMaster(ColorSequence solution, mpi::communicator world) :solution(solution), world(world) {}

RespondedGuess GameMaster::evaluate_guess(const ColorSequence& guess) {
  util::response res = ColorSequence::compare(guess, solution);
  return {res.perfect, res.color_only, guess};
}
