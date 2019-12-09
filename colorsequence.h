#include <vector>
#include <initializer_list>
#include <iterator>
#include <optional>

class ColorSequence {
 public:
  ColorSequence(unsigned char, std::vector<unsigned char>);
  std::optional<ColorSequence> operator+(unsigned int);
  const std::vector<unsigned char> seq;
  const unsigned char number_colors;
 private:
};
