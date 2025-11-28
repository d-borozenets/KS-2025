#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include "mpi_stub.h"
#else
#include <mpi.h>
#endif


int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    double *a;
    long long count = 500000000;

    // TODO: Rank 0 виділяє пам'ять
    // TODO: MPI_Scatter
    // TODO: локальна сума
    // TODO: MPI_Reduce
    // TODO: виміряти час

    // free(local_a);
    if (rank == 0)
        free(a);
    MPI_Finalize();
    return 0;
}
