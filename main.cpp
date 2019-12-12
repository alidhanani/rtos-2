#include <mpi.h>
#include <iostream>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/collectives.hpp>
#include "gamemaster.h"
#include "guesser.h"
#include "proposedguess.h"
#include "respondedguess.h"
namespace mpi = boost::mpi;

void run_gamemaster(mpi::communicator world);
void run_guesser(mpi::communicator world, unsigned int, unsigned int);
void report_response(mpi::communicator world, RespondedGuess);

int main(int argc, char** argv) {
  try {
    mpi::environment env;
    mpi::communicator world;
    if (world.rank() == 0) {
      std::cout << "Starting master " << world.rank() << std::endl;
      run_gamemaster(world);
    } else {
      std::cout << "Starting guesser " << world.rank() - 1 << std::endl;
      run_guesser(world, world.rank() - 1, world.size() - 1);
    }

    std::cout << "Thread " << world.rank() << " signing off!" << std::endl;
  } catch (const std::runtime_error& error) {
    std::cout << "Received unexpected error:" << std::endl;
    std::cout << error.what();
    return 1;
  }

  return 0;
}

void run_gamemaster(mpi::communicator world) {
  GameMaster master = GameMaster::with_random_solution(util::number_spaces, util::number_colors);
  std::cout << "Master using solution: " << master.solution.pretty_print() << std::endl;
    
  RespondedGuess response;
  int guess_number = 0;
  do {
    ProposedGuess proposed_guess;
    world.recv(mpi::any_source, 0, proposed_guess);
    std::cout << "Received proposed guess: " << proposed_guess.guess_number << std::endl;
    if (proposed_guess.guess_number != guess_number) {
      // Ignore the proposed_guess since it is outdated
      std::cout << "Ignoring outdated guess" << std::endl;
      continue;
    }

    response = master.evaluate_guess(proposed_guess.color_sequence);
    report_response(world, response);
    guess_number++;
  } while (response.perfect != util::number_spaces);
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

void run_guesser(mpi::communicator world, unsigned int id, unsigned int number_guessers) {
  Guesser guesser = {id, number_guessers, util::number_colors, util::number_spaces};
  
  while (true) {
    while (guesser.current_guess.has_value()
           && !guesser.is_plausible_guess(guesser.current_guess.value())) {
      std::cout << id << " with guess value "
                << guesser.current_guess.value().pretty_print() << std::endl;
      if (world.iprobe(mpi::any_source, 0).has_value()) {
        RespondedGuess responded_guess;
        std::cout << "beginning blocking read 1 - " << id << std::endl;
        world.recv(0, 0, responded_guess);
        std::cout << "finishing blocking read 1 - " << id << std::endl;
        if (responded_guess.perfect == util::number_spaces) {
          std::cout << "Guesser " << id
                    << " done. Other node found answer." << std::endl;
          return;
        }
        guesser.report_guess(responded_guess);
      }
      
      guesser.current_guess = (guesser.current_guess.value() + number_guessers);
    }

    // guesser.current_gues is now empty or plausible
    if (!guesser.current_guess.has_value()) {
      std::cout << "Guesser " << id << " done. Exhausted all options." << std::endl;
      return;
    }

    // guesser.current_guess is plausible, let's report it
    ProposedGuess proposed_guess = {guesser.guess_number(), guesser.current_guess.value()};
    std::cout << "beginning blocking write 1 - " << id << std::endl;
    world.send(0, 0, proposed_guess);
    std::cout << "finishing blocking write 1 - " << id << std::endl;

    // The master node will respond
    RespondedGuess responded_guess;
    std::cout << "beginning blocking read 2 - " << id << std::endl;
    world.recv(0, 0, responded_guess);
    std::cout << "finishing blocking read 2 - " << id << std::endl;
    if (responded_guess.perfect == util::number_spaces) {
      std::cout << "Guesser " << id
                << " done. I had just made a guess." << std::endl;
      return;
    }
    guesser.report_guess(responded_guess);
    if (responded_guess.color_sequence.seq == guesser.current_guess.value().seq) {
      // Our guess was used, so we should move to the next one
      guesser.current_guess = (guesser.current_guess.value() + number_guessers);
    }
    
  };
}
