#pragma once

namespace util {  
  struct response {
    unsigned int perfect;
    unsigned int color_only;
  };

  struct guess {
    const ColorSequence color_sequence;
    const response r;
  };

  // TODO: Could we make this configurable
  constexpr unsigned int number_spaces = 4;
  constexpr unsigned char number_colors = 2;
}
