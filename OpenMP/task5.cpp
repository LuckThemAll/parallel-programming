#include <cstdio>
#include <omp.h>
#include <vector>
#include <cstdlib>

#define lli long long int

int main(int argc, char *argv[])
{
//    system("chcp 65001");
    int matrix_size = atoi(argv[1]), threads_num = atoi(argv[2]);
    std::vector<int> matrix_1(matrix_size*matrix_size), matrix_2(matrix_size*matrix_size);
    std::vector<lli> product_matrix(matrix_size*matrix_size);
    for (int i = 0; i < matrix_size; ++i)
    {
        matrix_1[i] = 2;
        matrix_2[i] = 2;
        product_matrix[i] = 0;
    }
    printf("Threads in use: %d\n", threads_num);

    double start_1 = omp_get_wtime();
    #pragma omp parallel for num_threads(threads_num)
    for(int i = 0; i < matrix_size; i++ )
        for(int j = 0; j < matrix_size; j++ )
            for(int k = 0; k < matrix_size; k++ )
                product_matrix[j * matrix_size + i] += matrix_1[j * matrix_size + k] * matrix_2[k * matrix_size + i];
    double end_1 = omp_get_wtime();

    printf("Time of execution ijk: %.17lf\n", end_1-start_1);
///////////////////////////////////////////////////////////////////
    for (int i = 0; i < matrix_size*matrix_size; ++i)
        product_matrix[i] = 0;

    double start_2 = omp_get_wtime();
    #pragma omp parallel for num_threads(threads_num)
    for(int i = 0; i < matrix_size; i++ )
        for(int k = 0; k < matrix_size; k++ )
            for(int j = 0; j < matrix_size; j++ )
                product_matrix[j * matrix_size + i] += matrix_1[j * matrix_size + k] * matrix_2[k * matrix_size + i];
    double end_2 = omp_get_wtime();

    printf("Time of execution ikj: %.17lf\n", end_2-start_2);
////////////////////////////////////////////////////////////////
    double start_3 = omp_get_wtime();
    #pragma omp parallel for num_threads(threads_num)
    for(int j = 0; j < matrix_size; j++ )
        for(int k = 0; k < matrix_size; k++ )
            for(int i = 0; i < matrix_size; i++ )
                product_matrix[j * matrix_size + i] += matrix_1[j * matrix_size + k] * matrix_2[k * matrix_size + i];
    double end_3 = omp_get_wtime();

    printf("Time of execution jki: %.17lf\n", end_3-start_3);
    ////////////////////////////////////////////////////////////////
    double start_4 = omp_get_wtime();
    #pragma omp parallel for num_threads(threads_num)
    for(int k = 0; k < matrix_size; k++ )
        for(int j = 0; j < matrix_size; j++ )
            for(int i = 0; i < matrix_size; i++ )
                product_matrix[j * matrix_size + i] += matrix_1[j * matrix_size + k] * matrix_2[k * matrix_size + i];
    double end_4 = omp_get_wtime();

    printf("Time of execution kji: %.17lf\n", end_4-start_4);

}