#include <cstdio>
#include <windows.h>
#include <omp.h>
#include <vector>
#include <cstdlib>

int main(int argc, char *argv[])
{
    system("chcp 65001");
    int vector_size = atoi(argv[1]), max_elem = 0;
    int threads_num = atoi(argv[2]);
    std::vector<int> vector(vector_size);
    for (int i = 0; i < vector_size; ++i)
        vector[i] = rand();
    auto start = omp_get_wtime();
    printf("Используется нитей: %d\n", threads_num);
    #pragma omp parallel for reduction(max: max_elem) num_threads(threads_num)
    for (int i = 0; i < vector_size; i++) {
        max_elem = std::max(max_elem, vector[i]);
    }
    auto end = omp_get_wtime();
    printf("Максимальный элемент: %d\n", max_elem);
    printf("Время выполнения: %.17lf\n", end-start);

}