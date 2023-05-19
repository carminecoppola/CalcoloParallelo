#include <stdio.h>		//lettura
#include <stdlib.h>
#include <omp.h>		//per progammare parallel

int main () {
	int i, N, t, nloc, indice;
	float *a, *b, *c;
	
	printf("Inserire N:  \n");
	scanf(" %d", &N);
	
	//allocazione
	a = (float *)calloc(N, sizeof(float));
	b = (float *)calloc(N, sizeof(float));
	c = (float *)calloc(N, sizeof(float));
	
	
	//lettura
	printf("Inserire gli elementi del vettore a\n");
	for(i = 0; i < N; i++)
	{
		scanf(" %f", &a[i]);
	}
	printf("Inserire gli elementi del vettore b\n");
	for(i = 0; i < N; i++)
	{
		scanf(" %f", &b[i]);
	}
	
	
	//Inizio direttiva
	#pragma omp parallel private(nloc, i, indice) shared(a,b,c)
	{
		t = omp_get_num_threads(); //ritorna il numero totale dei core
		nloc = N/t;
		
		// identificativo del thread con il numero totale dei threads 
		printf("Sono %d, di %d: numeri %d\n", omp_get_thread_num(),t,nloc);
		
		for(i = 0; i < nloc; i++)
		{
			indice = i + nloc*omp_get_thread_num();
			c[indice] = a[indice] + b[indice];
		}
	}//Fine direttiva
	
	//Stampa
	printf("Stampa dei vettori");
	for(i = 0; i < N ; i++)
	{
		printf( " %f\n",c[i]);
		
	}
	
}
