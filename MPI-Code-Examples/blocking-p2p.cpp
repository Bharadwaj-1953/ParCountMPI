#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::cout << "Hello from processor " << rank;
    std::cout << " of " << size << std::endl;

    int data = 0, count = 1; 
    if (rank == 0) { 
	data = -56789; 
	MPI_Send(&data, count, MPI_INT, 1, 0, MPI_COMM_WORLD); 
    } else if (rank == 1) { 
	MPI_Recv(&data, count, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
	printf("Process 1 received integer %d from process 0\n", data); 
    }

    MPI_Finalize();
    return 0;
}
