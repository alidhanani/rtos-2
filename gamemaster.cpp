#include <initializer_list>
#include <iostream>
#include <random>

class GameMaster {
public:
  GameMaster RandomSolution(int num_colors, int num_spaces) {
    
    return GameMaster {'a'};
  }

private:
  GameMaster(std::initializer_list<char> lst) :solution{new char[lst.size()]} {
    std::copy(lst.begin(), lst.end(), solution);
  }

  ~GameMaster() {
    delete[] solution;
  }

  char* solution;  
};
