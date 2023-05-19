
/*Esercizio: Somma N numeri, 
Implementiamo la 1 Strategia: */


#include <stdio.h>		//lettura
#include <stdlib.h>
#include <omp.h>		//per progammare parallel

int main () 
{
	int i, N, t, nloc;
	float *a, sumtot, sum;
	sumtot = 0;
	
	printf("Inserire N:  \n");
	scanf(" %d", &N);
	
	//Allocazione
	a = (float *)calloc(N, sizeof(float));
	
	
	//Lettura
	printf("Inserire gli elementi da sommare: \n");
	for(i = 0; i < N; i++)
	{
		scanf(" %f", &a[i]);
	}
	
	
	//Inizio direttiva
	#pragma omp parallel private(sum, nloc, i) shared(sumtot)
	{//Se più di un'instruzione
	
		t = omp_get_num_threads(); //ritorna il numero totale dei core
		nloc = N/t;
		
		// identificativo del thread con il numero totale dei threads 
		printf("Sono %d, di %d: numeri %d\n", omp_get_thread_num(),t,nloc);
		
		sum = 0;
		for(i = 0; i < nloc; i++)
		{
			sum = sum + a[ i+ nloc * omp_get_thread_num()];
			
		}
		sumtot += sum;
		
	}//Fine direttiva
	
	//Stampa
	printf("Somma totale: %f\n",sumtot);
}
