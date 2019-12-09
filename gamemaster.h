#include <string>

struct response {
  int perfect;
  int color_only;
};

class GameMaster {
 public:
  static GameMaster* random_solution(int, unsigned char);
  std::string pretty_print_solution();
  response evaluate_guess(const unsigned char[]);
 private:
  GameMaster(unsigned char*,int,unsigned char,int*);
  const unsigned char* solution;
  const int num_spaces;
  const unsigned char num_colors;
  const int* color_count;
};
