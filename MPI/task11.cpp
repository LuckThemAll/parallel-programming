#include "mpi.h"
#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    int size, rank;
    MPI_Init(&argc, &argv);

    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // инициализация матрицы каждым процессом

    int N = 500;
    vector<vector<int>> A(500, vector<int>(500, 1)), B(500, vector<int>(500, 1)), result(500, vector<int>(500));

    MPI_Barrier(MPI_COMM_WORLD); //барьерная синхронизация процессов

    // начало замера времени для каждого процесса
    auto start_time = MPI_Wtime();
    // перемножение матриц
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result[i][j] = 0;
            for (int k = 0; k < N; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    // конец замера времени
    auto time_elapsed = MPI_Wtime() - start_time;
    // вывод время выполнения перемножения матриц на каждом процессе
    cout << "Process " << rank << ": " << time_elapsed << " seconds." << endl;

    MPI_Finalize();

    return EXIT_SUCCESS;
}