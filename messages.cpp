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
    MPI_Datatype types[3] = {MPI_UNSIGNED, MPI_UNSIGNED, MPI_UNSIGNED_CHAR};
    int lengths[3] = {1, 1, util::number_spaces};
    MPI_Aint offsets[3];
    MPI_Datatype mpi_guess_response;
    
    offsets[0] = offsetof(guess_response, perfect);
    offsets[1] = offsetof(guess_response, color_only);
    offsets[2] = offsetof(guess_response, guess);

    MPI_Type_create_struct(number_items, lengths, offsets, types, &mpi_guess_response);
    MPI_Type_commit(&mpi_guess_response);
    return mpi_guess_response;
  }

  guess convert_guess_response(guess_response guess_response) {
    util::response resp = {guess_response.perfect, guess_response.color_only};
    std::vector<unsigned char> seq(
                                   std::begin(guess_response.guess),
                                   std::end(guess_response.guess));
    ColorSequence color_sequence {util::number_colors, seq};
    return {color_sequence, resp};
  }
}
