#include <mpi.h>
#include <iostream>
#include "gamemaster.h"
#include "guesser.h"

int main(int argc, char** argv) {
  try {
    if (MPI_SUCCESS != MPI_Init(&argc, &argv)) {
      throw std::runtime_error("Unable to init mpi");
    }

    int rank;
    int num_processes;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    
    std::cout << "Very cool " << rank << " - " << num_processes << "\n";

    /*
    unsigned char number_colors = 2;
    unsigned int number_spaces = 4;
    GameMaster master = GameMaster::with_random_solution(number_spaces, number_colors);
    std::cout << "Master using solution: " << master.solution.pretty_print() << "\n";
    Guesser guesser {0, 1, number_colors, number_spaces};
    util::response response;
    do {
      std::optional<ColorSequence> guess = guesser.generate_plausible_guess();
      if (!guess.has_value()) {
        std::cout << "Exausted all possible guesses\n";
      }
      response = master.evaluate_guess(guess.value());
      std::cout
        << guess.value().pretty_print()
        << " perfect: " << response.perfect
        << " color_only: " << response.color_only
        << "\n";
      guesser.report_guess({guess.value(), response});
    } while (response.perfect != number_spaces);
    std::cout << "Found correct value\n";
    */
  } catch (const std::runtime_error& error) {
    std::cout << "Received unexpected error:\n";
    std::cout << error.what();
    return 1;
  }
  MPI_Finalize();
  return 0;
}

