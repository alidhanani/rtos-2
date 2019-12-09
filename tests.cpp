#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "gamemaster.h"

TEST_CASE("Test game master guess evaluation", "[evaluate_guess]") {
  unsigned char solution[] = {0,1,1,2,3};
  GameMaster master = GameMaster::with_solution(solution, 5, 5);

  SECTION("Perfect guess") {
    response r = master.evaluate_guess(solution);
    REQUIRE(r.perfect == 5);
    REQUIRE(r.color_only == 0);
  }

  SECTION("Bad guess") {
    unsigned char guess[] = {4,4,4,4,4};
    response r = master.evaluate_guess(guess);
    REQUIRE(r.perfect == 0);
    REQUIRE(r.color_only == 0);
  }

  SECTION("Ok guess") {
    unsigned char guess[] = {0,4,4,4,1};
    response r = master.evaluate_guess(guess);
    REQUIRE(r.perfect == 1);
    REQUIRE(r.color_only == 1);
  }
}
