#include <mpi.h>
#include <iostream>
#include "gamemaster.h"
#include "guesser.h"
#include "messages.h"

void run_gamemaster(MPI_Datatype, MPI_Datatype);
void run_guesser(unsigned int, unsigned int, MPI_Datatype, MPI_Datatype);
void report_response(const ColorSequence&, util::response, MPI_Datatype);

int main(int argc, char** argv) {
  try {
    MPI_Init(&argc, &argv);
    int global_rank;
    int global_num_processes;
    MPI_Comm_rank(MPI_COMM_WORLD, &global_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &global_num_processes);

    if (global_rank == 0) {
      run_gamemaster(messages::proposed_guess_type(),
                     messages::guess_response_type());
    } else {
      run_guesser(global_rank - 1,
                  global_num_processes - 1,
                  messages::proposed_guess_type(),
                  messages::guess_response_type());
    }
  } catch (const std::runtime_error& error) {
    std::cout << "Received unexpected error:\n";
    std::cout << error.what();
    return 1;
  }
  MPI_Finalize();
  return 0;
}

void run_gamemaster(MPI_Datatype mpi_proposed_guess, MPI_Datatype mpi_guess_response) {
  GameMaster master = GameMaster::with_random_solution(util::number_spaces, util::number_colors);
  std::cout << "Master using solution: " << master.solution.pretty_print() << "\n";
    
  util::response response;
  int guess_number = 0;
  do {
    messages::proposed_guess proposed_guess;
    MPI_Recv(&proposed_guess, 1, mpi_proposed_guess, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    if (proposed_guess.guess_number != guess_number) {
      // Ignore the proposed_guess since it is outdated
      continue;
    }

    std::vector<unsigned char> seq {std::begin(proposed_guess.guess), std::end(proposed_guess.guess)};
    ColorSequence color_seq = {util::number_colors,seq};
    response = master.evaluate_guess(color_seq);
    report_response(color_seq, response, mpi_guess_response);
    guess_number++;
  } while (response.perfect != util::number_spaces);
}

void report_response(const ColorSequence& guess, util::response response, MPI_Datatype mpi_guess_response) {
  // report response to user
  std::cout
    << guess.pretty_print()
    << " perfect: " << response.perfect
    << " color_only: " << response.color_only
    << "\n";

  messages::guess_response res = {response.perfect, response.color_only, {}};
  // TODO: There must be a better way
  // https://stackoverflow.com/questions/46212366/c-gives-strange-error-during-structure-initialization-with-an-array-inside
  for (unsigned char i : guess.seq) {
    res.guess[i] = guess.seq[i];
  }
  MPI_Bcast(&res, 1, mpi_guess_response, 0, MPI_COMM_WORLD);
}

void run_guesser(unsigned int id,
                 unsigned int number_guessers,
                 MPI_Datatype mpi_proposed_guess,
                 MPI_Datatype mpi_guess_response) {
  
  Guesser guesser = {id, number_guessers, util::number_colors, util::number_spaces};
  int guess_number = 0;
  
  while (true) {
    
    while (guesser.current_guess.has_value()
           && !guesser.is_plausible_guess(guesser.current_guess.value())) {
      int received_update; // TODO: Can we use a bool here? Should be false
      MPI_Iprobe(0, 0, MPI_COMM_WORLD, &received_update, MPI_STATUS_IGNORE);
      if (received_update) {
        messages::guess_response res;
        MPI_Bcast(&res,1,mpi_guess_response,0,MPI_COMM_WORLD);
        if (res.perfect == util::number_spaces) {
          return;
        }
        guess guess = messages::convert_guess_response(res);
        guesser.report_guess(guess);
      }
      
      guesser.current_guess = (guesser.current_guess.value() + number_guessers);
    }

    
    
    guess_number++;
  };
}
