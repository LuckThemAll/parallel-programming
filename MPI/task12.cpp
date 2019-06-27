#include "mpi.h"
#include <vector>
#include <iostream>

using namespace std;

void my_max(void *a, void *b, int *l, MPI_Datatype *type) {
    for (auto i = 0; i < *l; i++) {
        ((int*)b)[i] = max(((int*)a)[i], ((int*)b)[i]);
    }
}

int main(int argc, char **argv) {
    int rank, size, a, my_max_reduce, original_max_reduce;

    MPI_Init(&argc, &argv);
    MPI_Op max_op;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Op_create(&my_max, 1, &max_op);

    a = rank;
    MPI_Reduce(&a, &my_max_reduce, 1, MPI_INT, max_op, 0, MPI_COMM_WORLD);
    MPI_Reduce(&a, &original_max_reduce, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    MPI_Op_free(&max_op);
    if(rank == 0) {
        cout << "My max:  " << my_max_reduce << endl << "Mpi max: " << original_max_reduce << endl;
    }
    MPI_Finalize();
}