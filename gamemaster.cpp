#include <random>
#include <time.h>
#include <string>
#include "gamemaster.h"

GameMaster GameMaster::with_random_solution(unsigned int num_spaces, unsigned char num_colors) {
  srand(time(0));
  std::vector<unsigned char> solution(num_spaces);
  for (unsigned int i = 0; i < num_spaces; i++) {
    solution[i] = rand() % num_colors;
  }
  return GameMaster {ColorSequence {num_colors, solution}};
}

GameMaster::GameMaster(ColorSequence solution) :solution(solution) {}

std::string GameMaster::pretty_print_solution() {
  std::string solution_string;
  for (const unsigned char color : solution.seq) {
    // We add 97 so that each color is represented by an ASCII letter
    solution_string += color + 97;
  }
  return solution_string;
}

util::response GameMaster::evaluate_guess(const ColorSequence& guess) {
  return ColorSequence::compare(guess, solution);
}
