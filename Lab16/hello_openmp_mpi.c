#include <mpi.h>
#include <omp.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	
    // omp_set_num_threads(4);

    printf("Process %d of %d: starting...\n", world_rank, world_size);

    #pragma omp parallel
    {
        int thread_id   = omp_get_thread_num();
        int thread_count = omp_get_num_threads();

        printf("  [Process %d] Thread %d of %d\n",
               world_rank, thread_id, thread_count);
    }

    // Завершення MPI
    MPI_Finalize();
    return 0;
}
