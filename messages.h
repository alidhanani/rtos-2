#include <mpi.h>
#include "colorsequence.h"

namespace messages {
  struct proposed_guess {
    unsigned int guess_number;
    unsigned char guess[util::number_spaces];
  };
  
  struct guess_response {
    unsigned int perfect;
    unsigned int color_only;
    unsigned char guess[util::number_spaces];
  };

  MPI_Datatype proposed_guess_type();

  MPI_Datatype guess_response_type();

  // TODO: It's quite confusing having the guess, response, and guess_response types
  // Merge some things and rename
  guess convert_guess_response(guess_response);
}

