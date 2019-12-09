#include <random>
#include <time.h>
#include <string>
#include <stdexcept>
#include "gamemaster.h"

GameMaster GameMaster::with_random_solution(int num_spaces, unsigned char num_colors) {
  srand(time(0));
  std::vector<unsigned char> solution(num_spaces);
  for (int i = 0; i < num_spaces; i++) {
    solution[i] = rand() % num_colors;
  }
  return GameMaster::with_solution(solution, num_colors);
}

GameMaster GameMaster::with_solution(std::vector<unsigned char> solution, unsigned char num_colors) {
  std::vector<unsigned int> color_count(num_colors, 0);
  for (const unsigned char color : solution) {
    color_count[color]++;
  }
  return GameMaster {solution, color_count};
}


GameMaster::GameMaster(std::vector<unsigned char> sol, std::vector<unsigned int> col_count)
  :solution(sol), color_count(col_count) {}

std::string GameMaster::pretty_print_solution() {
  std::string solution_string;
  for (const unsigned char color : solution) {
    // We add 97 so that each color is represented by an ASCII letter
    solution_string += color + 97;
  }
  return solution_string;
}

util::response GameMaster::evaluate_guess(const std::vector<unsigned char>& guess) {
  if (guess.size() != solution.size()) {
    throw std::runtime_error("GameMaster::evaluate_guess called with guess of incorrect size");
  }
  
  int perfect = 0;
  int color_only = 0;
  std::vector<unsigned int> color_count_guess(color_count.size(), 0);
  for (unsigned int i = 0; i < solution.size(); i++) {
    if (guess[i] == solution[i]) {
      perfect++;
    }
    color_count_guess[guess[i]]++;
  }
  for (unsigned int i = 0; i < color_count.size(); i++) {
    color_only += std::min(color_count[i], color_count_guess[i]);
  }
  color_only -= perfect;
  return util::response {perfect, color_only};
}
