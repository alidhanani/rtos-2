#include <vector>

namespace util {
  struct response {
    int perfect;
    int color_only;
  };

  response compare_color_sequences(const std::vector<unsigned char>, const std::vector<unsigned char>);
}
