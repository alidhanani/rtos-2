#include <mpi.h>
#include <iostream>
#include "gamemaster.h"
#include "guesser.h"
#include "messages.h"

int main(int argc, char** argv) {
  try {
    MPI_Init(&argc, &argv);
    int global_rank;
    int global_num_processes;
    MPI_Comm_rank(MPI_COMM_WORLD, &global_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &global_num_processes);

    int tag = 0;

    MPI_Datatype mpi_proposed_guess = messages::proposed_guess_type();
    if (global_rank == 0) {
      // This node is a game master

      // Receive message from each computing node
      std::vector<messages::proposed_guess> responses(global_num_processes - 1);
      for (int i = 1; i < global_num_processes; i++) {
        messages::proposed_guess val;
        MPI_Status status;
        MPI_Recv(&val, 1, mpi_proposed_guess, i, tag, MPI_COMM_WORLD, &status);
        responses[i - 1] = val;
      }

      for (messages::proposed_guess response : responses) {
        std::cout << "Received guess: " << response.guess_number << " - ";
        for (int i=0; i < util::number_spaces; i++) {
          std::cout << static_cast<int>(response.guess[i]);
        }
        std::cout <<  "\n";
      }
    } else {
      // This node is a computing node
      messages::proposed_guess val = {100, {0,1,2,3}};
      MPI_Send(&val, 1, mpi_proposed_guess, 0, tag, MPI_COMM_WORLD);
    }

    MPI_Datatype mpi_guess_response = messages::guess_response_type();
    if (int i = 1)
    
    /*
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

