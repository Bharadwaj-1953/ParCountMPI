#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int data[2], total[2], count = 1; 
    data[0] = rank * 2;
    data[1] = rank * 10;

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Reduce(data, total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    std::cout << "Proc: " << rank << " after Reduce from Rank 0: " << total[0]
	<< "; " << total[1] << std::endl;
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Allreduce(data, total, 2, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    std::cout << "Proc: " << rank << " after allreduce: " << total[0] 
	<< "; " << total[1] << std::endl;

    MPI_Finalize();
    return 0;
}
