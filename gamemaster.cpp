#include <random>
#include <time.h>
#include <string>
#include "gamemaster.h"

GameMaster GameMaster::with_random_solution(int num_spaces, unsigned char num_colors) {
  srand(time(0));
  unsigned char solution[num_spaces];
  for (int i = 0; i < num_spaces; i++) {
    solution[i] = rand() % num_colors;
  }
  return GameMaster::with_solution(solution, num_spaces, num_colors);
}

GameMaster GameMaster::with_solution(unsigned char* solution, int num_spaces, unsigned char num_colors) {
  int color_count[num_colors] = {0};
  for (int i = 0; i < num_colors; i++) {
    color_count[solution[i]]++;
  }
  return GameMaster {solution, num_spaces, num_colors, color_count};
}


GameMaster::GameMaster(unsigned char* sol, int ns, unsigned char nc, int* col_count)
  :solution(sol), num_spaces(ns), num_colors(nc), color_count(col_count) {}

std::string GameMaster::pretty_print_solution() {
  std::string solution_string;
  for (int i = 0; i < num_spaces; i++) {
    // We add 97 so that each color is represented by an ASCII letter
    solution_string += solution[i] + 97;
  }
  return solution_string;
}

response GameMaster::evaluate_guess(const unsigned char guess[]) {
  int perfect = 0;
  int color_only = 0;
  int color_count_guess[num_colors] = {0};
  for (int i = 0; i < num_spaces; i++) {
    if (guess[i] == solution[i]) {
      perfect++;
    }
    color_count_guess[guess[i]]++;
  }
  for (int i = 0; i < num_colors; i++) {
    color_only += std::min(color_count[i], color_count_guess[i]);
  }
  color_only -= perfect;
  return response {perfect, color_only};
}
