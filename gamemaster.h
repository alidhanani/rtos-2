#include <string>
#include <vector>

struct response {
  int perfect;
  int color_only;
};

class GameMaster {
 public:
  static GameMaster with_random_solution(int, unsigned char);
  static GameMaster with_solution(std::vector<unsigned char>, unsigned char);
  std::string pretty_print_solution();
  response evaluate_guess(const std::vector<unsigned char>&);
 private:
  GameMaster(std::vector<unsigned char>,std::vector<unsigned int>);
  const std::vector<unsigned char> solution;
  const std::vector<unsigned int> color_count;
};
