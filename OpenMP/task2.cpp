#include <cstdio>
#include <windows.h>
#include <omp.h>
#include <vector>


int main(int argc, char *argv[])
{
    system("chcp 65001");
    int count = 0;
    int A[10], B[10], C[10], i, n;
    for (i = 0; i < 10; i++)
    {
        A[i] = i;
        B[i] = 2 * i;
        C[i] = 0;
    }

    #pragma omp parallel reduction (+: count)
    {
        count++;
        printf("Текущее значение count: %d\n", count);
    }
    printf("Число нитей: %d\n", count);

    #pragma omp parallel reduction (+: count) shared (A, B, C) private (i, n)
    {
        n = omp_get_thread_num();
        #pragma omp for
        for (i = 0; i < 10; i++)
            {
                C[i] = A[i] + B[i];
                printf("Нить %d сложила элементы с номером %d\n", n, i);
            }

    }
    std::vector<int> vec(10000, 1);
    int sum = 0, sum_red = 0;
    #pragma omp parallel for shared(sum) reduction(+: sum_red)
        for (i = 0; i < vec.size(); i++)
        {
            sum += vec[i];
            sum_red++;
        }
    printf("Сумма массива из 10000 элементов: %d\n", sum);
    printf("Опция reduction: %d\n", sum_red);

    sum = 0;
    #pragma omp parallel shared(sum)
    {
        int local_sum = 0;
        #pragma omp for
        for (int i = 0; i < vec.size(); i++)
        {
            local_sum += vec[i];
        }

        #pragma omp atomic
            sum += local_sum;
    }
    printf("Сумма с использованием дериктивы atomic: %d\n", sum);

    sum = 0;
    #pragma omp parallel
    {
        int local_sum = 0;
        #pragma omp for
        for (int i = 0; i < vec.size(); i++)
        {
            local_sum += vec[i];
        }

        #pragma omp critical
            sum += local_sum;
        }
    printf("Сумма с использованием дериктивы critical: %d\n", sum);

}