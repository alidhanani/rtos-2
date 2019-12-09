#include <stdexcept>
#include "util.h"

namespace util {
  
  response compare_color_sequences(const color_seq& seq1, const color_seq& seq2, unsigned int num_colors) {
    if (seq1.size() != seq2.size()) {
      throw std::runtime_error("Cannot compare color sequences of different sizes");
    }
    
    int perfect = 0;
    int color_only = 0;
    std::vector<unsigned int> color_count_seq1(num_colors, 0);
    std::vector<unsigned int> color_count_seq2(num_colors, 0);
    for (unsigned int i = 0; i < seq1.size(); i++) {
      if (seq1[i] == seq2[i]) {
        perfect++;
      }
      color_count_seq1[seq1[i]]++;
      color_count_seq2[seq2[i]]++;
    }
    
    for (unsigned int i = 0; i < num_colors; i++) {
      color_only += std::min(color_count_seq1[i], color_count_seq2[i]);
    }
    
    color_only -= perfect;
    return response {perfect, color_only}; 
  }
  
}
