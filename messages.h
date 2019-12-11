#include <mpi.h>
#include "util.h"

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

  util::guess convert_guess_response(guess_response);
}

