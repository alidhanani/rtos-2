#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "colorsequence.h"

TEST_CASE("Test color sequence comparison", "[ColorSequence::compare]") {
  const unsigned char num_colors = 5;
  const ColorSequence seq1 {num_colors, std::vector<unsigned char> {0,1,1,2,3}};

  SECTION("Perfect guess") {
    response r = ColorSequence::compare(seq1, seq1);
    REQUIRE(r.perfect == 5);
    REQUIRE(r.color_only == 0);
  }
  
  SECTION("Bad guess") {
    const ColorSequence seq2 {num_colors, std::vector<unsigned char> {4,4,4,4,4}};
    response r = ColorSequence::compare(seq1, seq2);
    REQUIRE(r.perfect == 0);
    REQUIRE(r.color_only == 0);
  }

  SECTION("Ok guess") {
    const ColorSequence seq2 {num_colors, std::vector<unsigned char> {0,4,4,4,1}};
    response r = ColorSequence::compare(seq1, seq2);
    REQUIRE(r.perfect == 1);
    REQUIRE(r.color_only == 1);
  }
}

TEST_CASE("Test color sequence addition", "[ColorSequence::operator+]") {
  SECTION("Simple addition") {
    ColorSequence seq {2, std::vector<unsigned char> {0, 0, 0}};
    std::optional<ColorSequence> res = seq + 1;
    REQUIRE(res.value().seq == std::vector<unsigned char> {1, 0, 0});
  }

  SECTION("overflow") {
    ColorSequence seq {2, std::vector<unsigned char> {1, 1, 1}};
    std::optional<ColorSequence> res = seq + 1;
    REQUIRE(res.has_value() == false);
  }

  SECTION("addition with carry") {
    ColorSequence seq {2, std::vector<unsigned char> {0, 1, 1}};
    std::optional<ColorSequence> res = seq + 1;
    REQUIRE(res.value().seq == std::vector<unsigned char> {1, 1, 1});
  }
}
