#include <iostream>
#include "gamemaster.h"

int main(int argc, char** argv) {
  GameMaster master = GameMaster::with_random_solution(10,10);
  std::cout << "Master using solution: " << master.pretty_print_solution();
  unsigned char guess[] = {0,1,2,3,4,5,6,7,8,9};
  master.evaluate_guess(guess);
  return 0;
}

