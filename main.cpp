#include <iostream>
#include "gamemaster.h"

int main(int argc, char** argv) {
  GameMaster* master = GameMaster::random_solution(10,10);
  std::cout << "Master using solution: " << master->pretty_print_solution();
  return 0;
}

