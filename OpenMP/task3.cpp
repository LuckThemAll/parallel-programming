#include <cstdio>
#include <windows.h>
#include <omp.h>
#include <vector>
#include <cstdlib>
#define lli unsigned long long int

int main(int argc, char *argv[])
{
    system("chcp 65001");
    lli vector_size = atoi(argv[1]), result = 0;
    int threads_num = atoi(argv[2]);
    std::vector<lli> vector_1(vector_size, 1), vector_2(vector_size, 1);
    auto start = omp_get_wtime();
    printf("Используется нитей: %d\n", threads_num);
    #pragma omp parallel num_threads(threads_num)
    {
        lli local_dot_prod = 0;

        #pragma omp for
        for(int i = 0; i < vector_size; ++i)
        {
            local_dot_prod += vector_1[i] * vector_2[i];
        }
        #pragma omp atomic
        result += local_dot_prod;

    }
    auto end = omp_get_wtime();
    printf("Результат скалярного произведения: %d\n", result);
    printf("Время выполнения: %.17lf\n", end-start);

}