#include <stdio.h>		//lettura
#include <stdlib.h>
#include <omp.h>		//per progammare parallel

int main () {
	int i, N, t, nloc, indice, id, step =0, r;
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
	#pragma omp parallel private(nloc, i, indice, id, step) shared(a, b, c, r)
	{
		t = omp_get_num_threads(); //ritorna il numero totale dei core
		nloc = N/t;
		r = N % t;
		id = omp_get_thread_num();
		 
		
		if (id < r)
		{
			nloc++;
			step = 0;
		} else {
			step = r;
		}
		
		for(i = 0; i < nloc; i++)
		{
			indice = i + nloc*omp_get_thread_num() + step;
			c[indice] = a[indice] + b[indice];
		}
		
		//Stampa
		printf( "\nSono %d, di %d: numeri %d, r = %d, passo = %d\n",id, t, nloc, r, step);
			
	}//Fine direttiva

	
}
