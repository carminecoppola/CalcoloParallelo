

#include <omp.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	#pragma omp parallel sections num_threads(7)
	{
		#pragma omp section
		{
			printf("\n1)Se ne sta occupando il thread numero: %d",omp_get_thread_num());
			printf("\n1)Hello world");
			printf("\n--------------------------------------------\n");
		}
		#pragma omp section
		{
			printf("\n2)Se ne sta occupando il thread numero: %d",omp_get_thread_num());
			printf("\n2)Hello world");
			printf("\n--------------------------------------------\n");
		}
		#pragma omp section
		{
			printf("\n3)Se ne sta occupando il thread numero: %d",omp_get_thread_num());
			printf("\n3)Hello world");
			printf("\n--------------------------------------------\n");
		}	
	}

	return 0;
}
