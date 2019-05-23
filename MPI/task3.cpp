#include <iostream>
#include "mpi.h"
using namespace std;
int main(int argc, char* argv[]){
    MPI_Init(&argc, &argv);
    int rank, n, i, message;
    double time_start, time_finish;
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &n);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    time_start = MPI_Wtime();
    if (rank == 0)
    {
        int mult = 1;
        for (i = 1; i < n; i++){
            MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE,
                     MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            if (message % 2 == 0){
                mult *= message;
            }
        }
        cout << "product is " << mult << endl;
    }
    else MPI_Send(&rank,1,MPI_INT,0,0,MPI_COMM_WORLD);
    time_finish = MPI_Wtime();
    if (rank == 0)
        cout << "time of execute = " << (time_finish-time_start) << endl;
    MPI_Finalize();
    return 0;
}