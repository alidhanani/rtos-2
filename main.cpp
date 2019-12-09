#include <iostream>
#include "gamemaster.h"

int main(int argc, char** argv) {
  try {
    GameMaster master = GameMaster::with_random_solution(10,10);
    std::cout << "Master using solution: " << master.pretty_print_solution() << "\n";
    ColorSequence guess {10, std::vector<unsigned char> {0,1,2,3,4,5,6,7,8,9}};
    master.evaluate_guess(guess);
  } catch (const std::runtime_error& error) {
    std::cout << "Received unexpected error:\n";
    std::cout << error.what();
    return 1;
  }
  return 0;
}

