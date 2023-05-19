/*Calcolo del Pi greco parallelo
	
*/

#include <stdio.h>
#include <omp.h>
#define N 100000000

int main(int argc, char **argv)
{

	long int i, n = N;
	double x, dx, f, sum, pi;
	
	printf("Numero di intervalli: %ld\n", n);
	sum = 0.0;
	
	dx = 1.0/(double)n;
	
	#pragma omp parallel for private(x, f, i) shared(dx, n) reduction(+:sum)
	for(i = 1; i <= n; i++){
		x = dx * ((double)(i-0.5));
		f = 4.0/(1.0 + x*x);
		
		//#pragma omp critical
		sum = sum + f;
	}
	
	pi = dx*sum;
	
	printf("PI greco: %.24f\n", pi); //24 numeri dopo la virgola
		

return 0;
}
