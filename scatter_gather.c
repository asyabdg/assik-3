#include <mpi.h>
#include <stdio.h>
#define N 2

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, size;
    double A[N][N] = {{1, 3}, {5, 4}};
    double B[N][N] = {{14, 4}, {44, 16}};
    double C[N][N] = {0}, localA[N], localC[N] = {0};
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Scatter(A, N, MPI_DOUBLE, localA, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(B, N*N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            localC[j] += localA[i] * B[i][j];

    MPI_Gather(localC, N, MPI_DOUBLE, C, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Result matrix C:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                printf("%.1f ", C[i][j]);
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}
