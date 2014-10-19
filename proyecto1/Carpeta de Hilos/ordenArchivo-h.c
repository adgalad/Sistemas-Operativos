#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include "ordenArchivo-h.h"

void llamarhoja (Arg_t *argumento) {
	printf("sapo\n");
	execlp("hojah",
			argumento->nodo[argumento->id].inicio, 
			argumento->nodo[argumento->id].fin);
}
void rama( Arg_t *argumento ) {
	Nodo *nodo = argumento->nodo;
	int id = argumento->id;
	int *arr = argumento->arr;
	pthread_join(nodo[nodo[id].h1].pid, NULL);
	pthread_join(nodo[nodo[id].h2].pid, NULL);
	int i;
	int j = nodo[nodo[id].h1].inicio,
		k = nodo[nodo[id].h2].inicio,
		n1 = nodo[nodo[id].h1].fin - j,
		n2 = nodo[nodo[id].h2].fin - k;

	int arr1[nodo[id].fin - nodo[id].inicio];
	for (i = 0 ; i < nodo[id].fin - nodo[id].inicio; i++) {
		arr1[i] = arr[nodo[id].inicio+i];
	}
	for ( i = nodo[id].inicio ; i < nodo[id].fin ; i++) {
			if (j == n1 )
				arr[nodo[id].inicio+i] = arr1[k++];
			else if ( k == n2)
				arr[nodo[id].inicio+i] = arr1[j++];
			else if (arr1[j] < arr1[k])
				arr[nodo[id].inicio+i] = arr1[j++];
			else 
				arr[nodo[id].inicio+i] = arr1[k++];
	}
	if ( id != 0 ) {
		pthread_exit(NULL);
	}
}

int main(int argv, char **argc) {
	int  n = atoi(argc[2]);
	int i;
	//int arr[atoi(argc[1])];
	int arr[] = {9,5,6,3,88,4,4,5,1,5,18,16,11,17,19,10,25,1};
	int m = pow(2,n)-1;
	FILE *fp;
	Nodo nodo[m];
	nodo[0].inicio = 0;
	nodo[0].fin = atoi(argc[1]) - 1;
	nodo[0].pid = 0;

	/*
	if ( (fp = fopen(argc[3], "rb")) == NULL ){
		perror("fopen: Error al abrir el archivo");
	}
	if ( fread(&arr, 4, atoi(argc[1]), fp) == 0 ) {
		perror("fread: Error al leer el archivo");
	}
	fclose(fp);
	*/

	for (i=1; i < m ; i++) {
		nodo[i].padre = (i-1)/2;
		int medio = nodo[nodo[i].padre].fin - nodo[nodo[i].padre].inicio;
		if ( i % 2 == 0) {
			if (medio % 2 == 0) {
				medio /= 2;
			}
			else{                
				medio = medio/2 +1;
			}
			nodo[i].inicio = medio;
			nodo[i].fin = nodo[nodo[i].padre].fin;
		}
		else {
			nodo[i].inicio = nodo[nodo[i].padre].inicio;
			nodo[i].fin = medio/2;
		}
		nodo[i].h1 = 2*i + 1;
		nodo[i].h2 = 2*i + 2;

		Arg_t argumento;
		argumento.id = i;
		argumento.nodo = nodo;
		argumento.arr = arr;

		if ( i < pow(2,n-1) - 1 ) {
			if (pthread_create( &nodo[i].pid, NULL, rama, (void *) &argumento) ) {
				perror("Error al crear thread\n");
				exit(1);
			}		
		}
		else {
			printf("holasapoteton\n");
			if (pthread_create( &nodo[i].pid, NULL, llamarhoja, (void *) &argumento) ) {
				perror("Error al crear thread\n");
				exit(1);
			}	
		}		
	}
	Arg_t argumento;
	argumento.id = 0;
	argumento.nodo = nodo;
	argumento.arr = arr;
	rama(&argumento);
	
	
	
	return 0 ; 
}
