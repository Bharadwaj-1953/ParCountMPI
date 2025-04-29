#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::cout << "Hello from processor " << rank;
    std::cout << " of " << size << std::endl;

if (rank == 0) {
    int buffer = 12345;
    MPI_Request request;
    MPI_Isend(&buffer, 1, MPI_INT, 1, 999, MPI_COMM_WORLD, &request);
    MPI_Wait(&request, MPI_STATUS_IGNORE);
    printf("[Process %d] sent the value %d.\n", rank, buffer);
} else if (rank == 1) {
    int received;
    MPI_Request request;
    MPI_Irecv(&received, 1, MPI_INT, 0, 999, MPI_COMM_WORLD, &request);
    MPI_Wait(&request, MPI_STATUS_IGNORE);
    printf("[Process %d] received the value %d.\n", rank, received);
}

    MPI_Finalize();
    return 0;
}
