#include <iostream>
#include <mpi.h>
#include <vector>
using namespace std;

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int vector_size = 100000000;
    vector<int>vec_a(vector_size, 1);
    vector<int>vec_b(vector_size, 1);
    double start_time;
    if (rank == 0) {
        start_time = MPI_Wtime();
    }
    auto vec_size = vec_a.size();
    auto chunk_size = vec_a.size() / size;

    auto start_index = rank * chunk_size;
    auto last_index = start_index + chunk_size - 1;
    auto last_chunk_size = vec_size - (size - 1)*chunk_size;
    auto local_sum = 0;

    if (rank != size - 1)
        for (auto i = start_index; i <= last_index; ++i)
            local_sum += vec_a[i] * vec_b[i];
    else
        for (auto i = start_index; i < start_index + last_chunk_size; i++)
            local_sum += vec_a[i] * vec_b[i];

    int result = 0;
    MPI_Reduce(&local_sum, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0)
        cout << result << endl;
    if (rank == 0)
        cout << "Time spent: " << MPI_Wtime() - start_time << endl;

    MPI_Finalize();

    return EXIT_SUCCESS;
}
