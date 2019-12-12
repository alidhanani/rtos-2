#include <mpi.h>
#include <iostream>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/collectives.hpp>
#include <boost/lexical_cast.hpp>
#include "gamemaster.h"
#include "guesser.h"
#include "proposedguess.h"
#include "respondedguess.h"
namespace mpi = boost::mpi;

void run_gamemaster(mpi::communicator world, unsigned int, unsigned char);
void run_guesser(mpi::communicator world, unsigned int, unsigned int, unsigned int, unsigned char);
void report_response(mpi::communicator world, RespondedGuess);

int main(int argc, char** argv) {  
  unsigned int number_spaces;
  unsigned char number_colors;
  if (argc == 3) {
    number_spaces = boost::lexical_cast<unsigned int>(argv[1]);
    number_colors = boost::lexical_cast<unsigned int>(argv[2]);
  } else {
    number_spaces = 5;
    number_colors = 3;
  }
  
  try {
    mpi::environment env;
    mpi::communicator world;

    if (world.size() == 1) {
      std::cout << "Please use at least 2 processes when running the program" << std::endl;
      return 1;
    }
    
    if (world.rank() == 0) {
      run_gamemaster(world, number_spaces, number_colors);
    } else {
      run_guesser(world, world.rank() - 1, world.size() - 1, number_spaces, number_colors);
    }
  } catch (const std::runtime_error& error) {
    std::cout << "Received unexpected error:" << std::endl;
    std::cout << error.what();
    return 1;
  }

  return 0;
}

void run_gamemaster(mpi::communicator world,
                    unsigned int number_spaces,
                    unsigned char number_colors) {
  GameMaster master = GameMaster::with_random_solution(number_spaces, number_colors);
  std::cout << "Master using solution: " << master.solution.pretty_print() << std::endl;
    
  RespondedGuess response;
  int guess_number = 0;
  do {
    ProposedGuess proposed_guess;
    world.recv(mpi::any_source, 0, proposed_guess);
    if (proposed_guess.guess_number != guess_number) {
      // Ignore the proposed_guess since it is outdated
      continue;
    }

    response = master.evaluate_guess(proposed_guess.color_sequence);
    report_response(world, response);
    guess_number++;
  } while (response.perfect != number_spaces);
}

void report_response(mpi::communicator world, RespondedGuess response) {
  std::cout
    << response.color_sequence.pretty_print()
    << " perfect: " << response.perfect
    << " color_only: " << response.color_only
    << std::endl;
  
  for (int i = 1, number_nodes = world.size(); i < number_nodes; i++) {
    world.send(i, 0, response);
  }
}

void run_guesser(mpi::communicator world,
                 unsigned int id,
                 unsigned int number_guessers,
                 unsigned int number_spaces,
                 unsigned char number_colors) {
  Guesser guesser = {id, number_guessers, number_colors, number_spaces};
  
  while (true) {
    while (guesser.current_guess.has_value()
           && !guesser.is_plausible_guess(guesser.current_guess.value())) {
      if (world.iprobe(mpi::any_source, 0).has_value()) {
        RespondedGuess responded_guess;
        world.recv(0, 0, responded_guess);

        if (responded_guess.perfect == number_spaces) {
          return;
        }
        guesser.report_guess(responded_guess);
      }
      
      guesser.current_guess = (guesser.current_guess.value() + number_guessers);
    }
    // guesser.current_gues is now empty or plausible
    
    if (!guesser.current_guess.has_value()) {
      return;
    }

    // guesser.current_guess is plausible, let's report it
    ProposedGuess proposed_guess = {guesser.guess_number(), guesser.current_guess.value()};
    world.send(0, 0, proposed_guess);

    // The master node will respond
    RespondedGuess responded_guess;
    world.recv(0, 0, responded_guess);
    if (responded_guess.perfect == number_spaces) {
      return;
    }
    guesser.report_guess(responded_guess);
    if (responded_guess.color_sequence.seq == guesser.current_guess.value().seq) {
      // Our guess was used, so we should move to the next one
      guesser.current_guess = (guesser.current_guess.value() + number_guessers);
    }
    
  };
}
