#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char word[] = "Parallelization";
    int len = strlen(word);
    char recv;

    if (rank < len) {
        recv = word[rank];
        printf("Process %d received '%c'\n", rank, recv);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    // Reverse redistribution
    int reversed_rank = len - 1 - rank;
    if (rank < len) {
        printf("Reversed: Process %d gets '%c'\n", rank, word[reversed_rank]);
    }

    MPI_Finalize();
    return 0;
}
