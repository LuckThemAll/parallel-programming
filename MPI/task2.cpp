#include <iostream>
#include "mpi.h"
using namespace std;
int main(int argc, char* argv[]){
    MPI_Init(&argc, &argv);
    int rank, n, i, message;
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &n);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0)
    {
        MPI_Send(&rank,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
    }
    else {
        if (rank + 1 < n){
            MPI_Send(&rank,1,MPI_INT,rank + 1,0,MPI_COMM_WORLD);
        }
        MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD,
                 &status);
        cout << "Hello from process " << message << " to " << rank << endl;
    }
    MPI_Finalize();
    return 0;
}