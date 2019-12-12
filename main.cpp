#include <mpi.h>
#include <iostream>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/lexical_cast.hpp>
#include "gamemaster.h"
#include "guesser.h"
#include "respondedguess.h"
namespace mpi = boost::mpi;

int main(int argc, char** argv) {  
  unsigned int number_spaces;
  unsigned char number_colors;
  if (argc == 3) {
    number_spaces = boost::lexical_cast<unsigned int>(argv[1]);
    number_colors = boost::lexical_cast<unsigned int>(argv[2]);
  } else {
    number_spaces = 4;
    number_colors = 10;
  }
  
  try {
    mpi::environment env;
    mpi::communicator world;

    if (world.size() == 1) {
      std::cout << "Please use at least 2 processes when running the program" << std::endl;
      return 1;
    }
    
    if (world.rank() == 0) {
      GameMaster master = GameMaster
        ::with_random_solution(number_spaces, number_colors, world);
      master.run();
    } else {
      Guesser guesser = {world, world.rank() - 1, world.size() - 1, number_colors, number_spaces};
      guesser.run();
    }
  } catch (const std::runtime_error& error) {
    std::cout << "Received unexpected error:" << std::endl;
    std::cout << error.what();
    return 1;
  }

  return 0;
}
