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
  response res = ColorSequence::compare(guess, solution);
  return {res.perfect, res.color_only, guess};
}

void GameMaster::run() {
  std::cout << "Master using solution: " << solution.pretty_print() << std::endl;
  
  RespondedGuess response;
  int guess_number = 0;
  do {
    ProposedGuess proposed_guess;
    world.recv(mpi::any_source, 0, proposed_guess);
    if (proposed_guess.guess_number != guess_number) {
      // Ignore the proposed_guess since it is outdated
      continue;
    }
    
    response = evaluate_guess(proposed_guess.color_sequence);
    report_response(response);
    guess_number++;
  } while (response.perfect != solution.seq.size());
}

void GameMaster::report_response(RespondedGuess response) {
    std::cout
    << response.color_sequence.pretty_print()
    << " perfect: " << response.perfect
    << " color_only: " << response.color_only
    << std::endl;
  
  for (int i = 1, number_nodes = world.size(); i < number_nodes; i++) {
    world.send(i, 0, response);
  }
}
