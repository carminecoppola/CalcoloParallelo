/*Prodotto di matrice per vettore in sezione critica con reduction*/

#include <omp.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    double** A;
    double* b, * a, * r, * f;
    double alpha, beta;
    double out = 0;
    int N, M;
    double t0, t1;

    N = M = 4;
    r = (double*)calloc(M, sizeof(double));
    f = (double*)calloc(M, sizeof(double));
    a = (double*)calloc(N, sizeof(double));
    b = (double*)calloc(N, sizeof(double));
    A = (double**)calloc(N, sizeof(double*));

    for (int i = 0; i < N; ++i) {
        A[i] = (double*)calloc(N, sizeof(double));
    }

    for (int i = 0; i < N; ++i) {
        a[i] = i;
        b[i] = i+1;
        for (int j = 0; j < M; j++) {
            A[i][j] = i+j;
        }
    }

		printf("\nStampa della matrice A:\n");
		for(int i = 0 ; i < M; i++)
		{
			for(int j = 0; j < N; j++)
			{
				printf("%f ",A[i][j]);
			}
			printf("\n");
		}
		
		printf("\nStampa del vettore a:\n");
		for(int i = 0 ; i < M; i++)
		{
				printf("%f ",a[i]);
				
		}
		
		printf("\nStampa del vettore b:\n");
		for(int i = 0; i < M; i++)
		{
				printf("%f ",b[i]);
			
		}
		

    alpha = 3;
    beta = 2;

		double sum = 0;
    #pragma omp parallel sections num_threads(2) reduction(+:sum)
    {
        #pragma omp section
        {
            for (int i = 0; i < M; i++) 
            {
                for (int j = 0; j < N; ++j) 
                {
                    r[i] += alpha * A[i][j] * b[j];
                }
            }
        }
        #pragma omp section
        {
            for (int i = 0; i < M; i++) 
            {
                f[i] += (a[i] * beta);
            }
        }
        
        #pragma omp section
        {
		      for (int i = 0; i < M; ++i) 
		      {
		      	sum += r[i] + f[i];
		   		}
		  		out = sum;
	  		}
    }

    printf("\nalpha*A*b = ");

    for (int i = 0; i < M; ++i) {
        printf("%lf ", r[i]);
    }

    printf("\n\nout = %lf\n", out);

    return 0;
}

