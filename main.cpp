#include <mpi.h>
#include <iostream>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include "gamemaster.h"
#include "guesser.h"
#include "proposedguess.h"
#include "respondedguess.h"
namespace mpi = boost::mpi;

void run_gamemaster();
void run_guesser(unsigned int, unsigned int);
void report_response(const RespondedGuess&);

int main(int argc, char** argv) {
  try {
    mpi::environment env;
    mpi::communicator world;
    if (world.rank() == 0) {
      std::cout << "Starting master " << world.rank() << std::endl;
      run_gamemaster();
    } else {
      std::cout << "Starting guesser " << world.rank() - 1 << std::endl;
      run_guesser(world.rank() - 1, world.size() - 1);
    }

    std::cout << "Thread " << world.rank() << " signing off!" << std::endl;
  } catch (const std::runtime_error& error) {
    std::cout << "Received unexpected error:" << std::endl;
    std::cout << error.what();
    return 1;
  }

  return 0;
}

void run_gamemaster() {
  GameMaster master = GameMaster::with_random_solution(util::number_spaces, util::number_colors);
  std::cout << "Master using solution: " << master.solution.pretty_print() << std::endl;
    
  util::response response;
  int guess_number = 0;
  do {
    messages::proposed_guess proposed_guess;
    MPI_Recv(&proposed_guess, 1, mpi_proposed_guess, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    if (proposed_guess.guess_number != guess_number) {
      // Ignore the proposed_guess since it is outdated
      std::cout << "Ignoring outdated guess" << std::endl;
      continue;
    }

    std::vector<unsigned char> seq {std::begin(proposed_guess.guess), std::end(proposed_guess.guess)};
    ColorSequence color_seq = {util::number_colors,seq};
    response = master.evaluate_guess(color_seq);
    report_response(color_seq, response, mpi_guess_response);
    guess_number++;
  } while (response.perfect != util::number_spaces);
}

void report_response(const RespondedGuess& response) {
  std::cout
    << response.color_sequence.pretty_print()
    << " perfect: " << response.perfect
    << " color_only: " << response.color_only
    << std::endl;

  MPI_Bcast(&res, 1, mpi_guess_response, 0, MPI_COMM_WORLD);
}

void run_guesser(unsigned int id, unsigned int number_guessers) {
  Guesser guesser = {id, number_guessers, util::number_colors, util::number_spaces};
  int guess_number = 0;
  
  while (true) {
    
    while (guesser.current_guess.has_value()
           && !guesser.is_plausible_guess(guesser.current_guess.value())) {
      std::cout << id << " with guess value " << guesser.current_guess.value().pretty_print() << std::endl;
      int received_update;
      MPI_Iprobe(0, 0, MPI_COMM_WORLD, &received_update, MPI_STATUS_IGNORE);
      if (received_update) {
        messages::guess_response res;
        MPI_Bcast(&res,1,mpi_guess_response,0,MPI_COMM_WORLD);
        if (res.perfect == util::number_spaces) {
          std::cout << "Guesser " << id << " done. Other node found answer." << std::endl;
          return;
        }
        guess guess = messages::convert_guess_response(res);
        guesser.report_guess(guess);
      }
      
      guesser.current_guess = (guesser.current_guess.value() + number_guessers);
    }

    // guesser.current_gues is now empty or plausible
    if (!guesser.current_guess.has_value()) {
      std::cout << "Guesser " << id << " done. Exhausted all options." << std::endl;
      return;
    }

    // guesser.current_guess is plausible, let's report it
    messages::proposed_guess val = {guess_number, {}};
    // TODO: There must be a better way
    for (int i = 0; i < guesser.current_guess.value().seq.size(); i++) {
      val.guess[i] = guesser.current_guess.value().seq[i];
    }
    MPI_Send(&val, 1, mpi_proposed_guess, 0, 0, MPI_COMM_WORLD);

    // The master node will respond
    messages::guess_response res;
    MPI_Bcast(&res,1,mpi_guess_response,0,MPI_COMM_WORLD);
    if (res.perfect == util::number_spaces) {
      std::cout << "Guesser " << id << " done. I had just made a guess." << std::endl;
      return;
    }
    guess guess = messages::convert_guess_response(res);
    guesser.report_guess(guess);
    if (guess.color_sequence.seq == guesser.current_guess.value().seq) {
      // Our guess was used, so we should move to the next one
      guesser.current_guess = (guesser.current_guess.value() + number_guessers);
    }
    
    guess_number++;
  };
}
