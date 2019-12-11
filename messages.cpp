#include "messages.h"

namespace messages {
  MPI_Datatype proposed_guess_type() {
    int number_items = 2;
    MPI_Datatype types[2] = {MPI_UNSIGNED, MPI_UNSIGNED_CHAR};
    int lengths[2] = {1, util::number_spaces};
    MPI_Aint offsets[2];
    MPI_Datatype mpi_proposed_guess;

    offsets[0] = offsetof(proposed_guess, guess_number);
    offsets[1] = offsetof(proposed_guess, guess);

    MPI_Type_create_struct(number_items, lengths, offsets, types, &mpi_proposed_guess);
    MPI_Type_commit(&mpi_proposed_guess);
    return mpi_proposed_guess;
  }

  MPI_Datatype guess_response_type() {
    int number_items = 3;
    
  }
}
