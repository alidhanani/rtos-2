#include "guesser.h"

Guesser::Guesser(mpi::communicator world,
                 unsigned int id,
                 unsigned int number_nodes,
                 unsigned char number_colors,
                 unsigned int number_spaces)
  :world(world),
   id(id),
   number_nodes(number_nodes),
   previous_guesses(std::vector<RespondedGuess>()),
   number_colors(number_colors),
   number_spaces(number_spaces),
   current_guess(get_first_guess(id, number_spaces, number_colors)) {}

std::optional<ColorSequence> Guesser::get_first_guess(unsigned int id, unsigned int number_spaces, unsigned char number_colors) {
  ColorSequence zero {number_colors, std::vector<unsigned char>(number_spaces, 0)};
  return zero + id;
}

void Guesser::run() {
  while (true) {
    while (current_guess.has_value()
           && !is_plausible_guess(current_guess.value())) {
      if (world.iprobe(mpi::any_source, 0).has_value()) {
        RespondedGuess responded_guess;
        world.recv(0, 0, responded_guess);

        if (responded_guess.perfect == number_spaces) {
          return;
        }
        report_guess(responded_guess);
      }
      
      current_guess = (current_guess.value() + number_nodes);
    }
    // guesser.current_gues is now empty or plausible
    
    if (!current_guess.has_value()) {
      return;
    }

    // guesser.current_guess is plausible, let's report it
    ProposedGuess proposed_guess = {guess_number(), current_guess.value()};
    world.send(0, 0, proposed_guess);

    // The master node will respond
    RespondedGuess responded_guess;
    world.recv(0, 0, responded_guess);
    if (responded_guess.perfect == number_spaces) {
      return;
    }
    report_guess(responded_guess);
    if (responded_guess.color_sequence.seq == current_guess.value().seq) {
      // Our guess was used, so we should move to the next one
      current_guess = (current_guess.value() + number_nodes);
    }
    
  };
}

void Guesser::report_guess(const RespondedGuess guess) {
  previous_guesses.push_back(guess);
}

int Guesser::guess_number() {
  return previous_guesses.size();
}

bool Guesser::is_plausible_guess(const ColorSequence& proposed_guess) {
  for (const RespondedGuess& guess : previous_guesses) {
    if (!is_plausible_guess(guess, proposed_guess)) {
      return false;
    }
  }
  return true;
}

bool Guesser::is_plausible_guess(const RespondedGuess& guess, const ColorSequence& proposed_guess) {
  response response = ColorSequence::compare(guess.color_sequence, proposed_guess);
  return response.perfect == guess.perfect
    && response.color_only == guess.color_only;
}
