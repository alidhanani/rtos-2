#include <string>

class GameMaster {
 public:
  static GameMaster* random_solution(int, int);
  std::string pretty_print_solution();
 private:
  GameMaster(char*,int,int);
  const char* solution;
  const int num_spaces;
  const int num_colors;
};

