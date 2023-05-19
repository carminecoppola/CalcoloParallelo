/* Prodotto Matrice per vettore con la 2 strattegia */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>



int *matxvet(int m, int n, int *b, int **matrix)
{

	int i,j;
	int *x;
	
	x = (int*) calloc(m,sizeof(int));
	

	

	#pragma omp parallel for default(none)shared(m,n,matrix,x,b)private(i,j)
		for(i = 0; i < n; i++)
		{
			for(j = 0; j < m; j++)
			{
				x[i] += matrix[j][i]*b[j];

			}
		}
		
		return x;

}

int main() {

	int m = 3,n = 3;

	int **matrix;
	int *b, *result;
	
	b = (int*) calloc(m,sizeof(int));
	result = (int*) calloc(n,sizeof(int));
	
	matrix = (int**) calloc(n,sizeof(int*));
	
	for(int i = 0; i < m; i++)
	{
		matrix[i] = (int*) calloc(m,sizeof(int));
	}
	
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
		{
			matrix[i][j] = i + j;
		}
	}
	
	for(int i = 0; i< m; i++)
	{
		b[i] = i + 1;
	}


	result = matxvet(m,n,b,matrix);
	
	printf("\n Stampiamo il vettore risultante:");
	for(int i = 0; i< n; i++)
	{
		printf("\n %d\n", result[i]);
	}

	return 0;
}




