#include <stdio.h>
#include <omp.h>
#include <vector>
#include <algorithm>
int main(int argc, char *argv[]){
	#ifdef _OPENMP
	printf("OpenMP is supported!\n");
	#endif
	printf("Последовательная область 1\n");
	int a[8], index = 0;
	for (int i = 0; i < 8; ++i)
		a[i] = 0;
	omp_set_num_threads(2);
	#pragma omp parallel shared(a, index) num_threads(8)
	{
		int count, num;
		printf("Параллельная область\n");
		count=omp_get_num_threads();
		num=omp_get_thread_num();
		
		if (num == 0) 
		{
			printf("Всего нитей: %d\n", count);
			a[index] = num;
			index++;
		}
		else 
		{
			printf("Нить номер %d\n", num);
			a[index] = num;
			index++;
		}
	}
	#pragma omp parallel
	{
		printf("Параллельная область 2\n");
	}
	printf("Обратный порядок:\n");
	for (int i = 7; i >= 0; --i)
		printf("%d\n", a[i]);
	printf("Последовательная область 2\n");
}
