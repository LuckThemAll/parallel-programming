#include "mpi.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    int size, rank1, rank2, processes;

    MPI_Status status;
    MPI_Comm inter_communicator;

    char slave[] = "./task16_slave";

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_spawn(slave, MPI_ARGV_NULL, 3, MPI_INFO_NULL, 0, MPI_COMM_SELF, &inter_communicator,
                   MPI_ERRCODES_IGNORE);

    MPI_Recv(&rank1, 1, MPI_INT, 0, 0, inter_communicator, &status);
    MPI_Recv(&rank2, 1, MPI_INT, 1, 1, inter_communicator, &status);
    MPI_Recv(&processes, 1, MPI_INT, 2, 2, inter_communicator, &status);

    cout << "Total number of processes " << processes << endl;
    cout << "Slaves " << rank1 << " and " << rank2 << " are working" << endl;

    MPI_Finalize();
    return EXIT_SUCCESS;
}