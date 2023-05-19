/* Prodotto matrice per scalare utilizzando la prima strategia, 
   la seconda è analoga basta invertire i for nel pragma
*/


#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<unistd.h>
#include<omp.h>

int main() {
    int N;
    double t1,t2;
    
    printf("Inserisci le dimensioni della matrice: ");
    scanf("%d", &N);
    
    // Allocazione dinamica della matrice
    int *matrix = (int*)calloc(N * N, sizeof(int *));
    
  

    // Inizializzazione della matrice
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[(i * N) + j]= i * j;
        }
    }

    // Stampa della matrice
    printf("\nMatrice Iniziale:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[(i * N) + j]);
        }
        printf("\n");
    }


	//Tempo iniziale 
	t1 = omp_get_wtime();

	#pragma omp parallel for shared(matrix)schedule(guided)num_threads(4)
		for(int i = 0; i < N; i++)
		{
			for(int j = 0; j < N; j++)
			{
			 	matrix[(i * N)+ j ] = matrix[(i * N) + j] * 2;
			}
		}
		
		
	//Tempo finale 
	t2 = omp_get_wtime();
	
	printf("\nTempo iniziale: %lf", t1);
	printf("\nTempo finale: %lf", t2);

	// Stampa della matrice
    printf("\n\nMatrice Finale:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[(i * N) + j]);
        }
        printf("\n");
    }
    
    
    printf("\nTempo totale: %lf \n", t2-t1);
    
    
    return 0;

}

