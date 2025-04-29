#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int data = 0, count = 1; 
    double time00, time01, time02;

    MPI_Barrier(MPI_COMM_WORLD);
    for (int k = 0; k < 100; k++) {
	time00 = MPI_Wtime();
	if (rank == 0) { 
	    data = -56789; 
	    for (int i = 1; i < size; i++) {
		MPI_Send(&data, count, MPI_INT, i, 0, MPI_COMM_WORLD); 
	    }
	} else { 
	    MPI_Recv(&data, count, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
	}
	if (rank == 0) { 
	    time01 += MPI_Wtime();
	}
	MPI_Barrier(MPI_COMM_WORLD);
	time00 = MPI_Wtime();
	MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
	if (rank == 0) { 
	    time02 += MPI_Wtime();
	}
    }
    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == 0) { 
	std::cout << "Manual Bcast from Rank 0: " << time01 << std::endl;
	std::cout << "Bcast call total from Rank 0: " << time02 << std::endl;
    }

    MPI_Finalize();
    return 0;
}
