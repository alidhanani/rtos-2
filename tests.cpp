#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "util.h"

TEST_CASE("Test color sequence comparison", "[util::compare_color_sequences]") {
  std::vector<unsigned char> seq1 = {0,1,1,2,3};
  unsigned int num_colors = 5;

  SECTION("Perfect guess") {
    util::response r = util::compare_color_sequences(seq1, seq1, num_colors);
    REQUIRE(r.perfect == 5);
    REQUIRE(r.color_only == 0);
  }

  SECTION("Bad guess") {
    std::vector<unsigned char> seq2 = {4,4,4,4,4};
    util::response r = util::compare_color_sequences(seq1, seq2, num_colors);
    REQUIRE(r.perfect == 0);
    REQUIRE(r.color_only == 0);
  }

  SECTION("Ok guess") {
    std::vector<unsigned char> seq2 = {0,4,4,4,1};
    util::response r = util::compare_color_sequences(seq1, seq2, num_colors);
    REQUIRE(r.perfect == 1);
    REQUIRE(r.color_only == 1);
  }
}
