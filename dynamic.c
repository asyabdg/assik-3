#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    MPI_Comm parent;
    MPI_Comm_get_parent(&parent);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (parent == MPI_COMM_NULL) {
        int n = 3;  // Кол-во процессов
        MPI_Comm intercomm;
        MPI_Comm_spawn("dynamic_spawn", MPI_ARGV_NULL, n,
                       MPI_INFO_NULL, 0, MPI_COMM_WORLD, &intercomm, MPI_ERRCODES_IGNORE);
    }

    MPI_Comm_get_parent(&parent);
    if (parent != MPI_COMM_NULL) {
        int parent_rank;
        MPI_Comm_rank(parent, &parent_rank);
        printf("I am %d process from %d processes! My parent is %d\n", rank, size, parent_rank);
    }

    MPI_Finalize();
    return 0;
}
