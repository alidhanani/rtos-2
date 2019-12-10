#include <mpi.h>
#include <iostream>
#include "gamemaster.h"
#include "guesser.h"

int main(int argc, char** argv) {
  try {
    if (MPI_SUCCESS != MPI_Init(&argc, &argv)) {
      throw std::runtime_error("Unable to init mpi");
    }

    int global_rank;
    int global_num_processes;
    MPI_Comm_rank(MPI_COMM_WORLD, &global_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &global_num_processes);

    int color;
    MPI_Comm intra_comm;
    if (global_rank == 0) {
      // This is the master node
      color = 0;
      MPI_Comm_split(MPI_COMM_WORLD, color, 0, &intra_comm);
    } else {
      color = 1;
      MPI_Comm_split(MPI_COMM_WORLD, color, 0, &intra_comm);
    }
    int local_rank;
    int local_num_processes;
    MPI_Comm_rank(intra_comm, &local_rank);
    MPI_Comm_size(intra_comm, &local_num_processes);
    std::cout << "Cool -"
              << " Global rank: " << global_rank
              << " Global num processes: " << global_num_processes
              << " local rank: " << local_rank
              << " local num processes: " << local_num_processes
              << "\n";

    MPI_Comm inter_comm;
    if (global_rank == 0) {
      MPI_Intercomm_create(intra_comm, 0, MPI_COMM_WORLD, 1, 0, &inter_comm);
    } else {
      MPI_Intercomm_create(intra_comm, 0, MPI_COMM_WORLD, 0, 0, &inter_comm);
    }

    int val;
    if (global_rank == 0) {
      // change rank of root in group a to 1?
      val = 100;
      MPI_Bcast(&val, 1, MPI_INT, MPI_ROOT, inter_comm);
    } else if (global_rank == 1) {
      MPI_Bcast(&val, 1, MPI_INT, 0, inter_comm);
    } else {
      MPI_Bcast(&val, 1, MPI_INT, 0, inter_comm);
    }

    std::cout << "Global rank: " << global_rank << " val: " << val << "\n";
    
    MPI_Comm_free(&intra_comm);
    MPI_Comm_free(&inter_comm);

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

