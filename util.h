#pragma once

// TODO: Merge with colorsequence.h?
namespace util {  
  struct response {
    unsigned int perfect;
    unsigned int color_only;
  };

  // TODO: Could we make this configurable
  constexpr unsigned int number_spaces = 4;
  constexpr unsigned char number_colors = 2;
}
