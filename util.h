#include <vector>

namespace util {
  struct response {
    int perfect;
    int color_only;
  };
  
  response compare_color_sequences(std::vector<unsigned char>, std::vector<unsigned char>, unsigned int);
}
