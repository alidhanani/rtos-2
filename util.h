#include <vector>

namespace util {
  using color_seq = std::vector<unsigned char>;
  
  struct response {
    int perfect;
    int color_only;
  };
  
  response compare_color_sequences(const color_seq&, const color_seq&, unsigned int);
}
