#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>

//Dimensione della matrice
#define n 3

int main()
{

	int **matrix;
	int *diag;

	//Alloco la matrice
	matrix = (int**) calloc(n,sizeof(int*));
	diag = (int*) calloc(n,sizeof(int));

	for(int i = 0; i < n; i++)
	{
		matrix[i] = (int*) calloc(n,sizeof(int));
	}
	
	
	//Riempio la matrice
	for(int i = 0; i < n; i++)
	{
		for(int j = 0 ; j < n ; j++)
		{
				matrix[i][j] = i + j;
		}
	}
	
	printf("\nStampiamo la matrice:\n");
	for(int i = 0; i< n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
	
	
	//Mi calcolo la diagonale e la salvo
	#pragma omp parallel for shared(matrix,diag) num_threads(2)
		for(int i = 0; i < n; i++)
		{
			diag[i] = matrix[i][i];
		}
	
	printf("\nStampo la diagonale:\n");
	for(int i = 0 ; i < n; i ++)
	{
			printf(" %d \n",diag[i]);
	}

	int max_value = diag[0];
	
	//Calcolo il massimo del vettore diagonale
	#pragma omp parallel for shared(diag) reduction(max: max_value) num_threads(2)
		for(int i = 1 ; i < n ; i++)
		{
			if(diag[i] > max_value)
			{
				max_value = diag[i];
			}
		}
	
	printf("\nMassimo valore del vettore diagonale: %d\n", max_value);

	return 0;
}

