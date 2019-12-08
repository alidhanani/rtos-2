#include <random>
#include <time.h>
#include <string>
#include "gamemaster.h"

GameMaster* GameMaster::random_solution(int num_spaces, int num_colors) {
  srand(time(0));
  char solution[num_spaces];
  for (int pos = 0; pos < num_spaces; pos++) {
    solution[pos] = rand() % num_colors;
  }
  return new GameMaster(solution, num_spaces, num_colors);
}

GameMaster::GameMaster(char* sol, int ns, int nc)
  :solution(sol), num_spaces(ns), num_colors(nc) {}

std::string GameMaster::pretty_print_solution() {
  std::string solution_string;
  for (int i=0; i<num_spaces; i++) {
    // We add 97 so that each color is represented by an ASCII letter
    solution_string += solution[i] + 97;
  }
  return solution_string;
}

