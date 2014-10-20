#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include "ordenArchivo-h.h"
#include <time.h>


Nodo *nodo;
int *arr;
int n;

int main(int argv, char **argc) {
	time_t start, stop;

	time(&start);

	n = atoi(argc[2]);
	int i;
	char *nombreArchivo = argc[3];
	char *archivoSalida = argc[4];

	int m = pow(2,n)-1;
	FILE *fp;
	arr  = (int *) malloc(sizeof(int)*atoi(argc[1]));
	nodo = (Nodo*) malloc(sizeof(Nodo)*pow(2,n-1));
	nodo[0].inicio = 0;
	nodo[0].fin = atoi(argc[1]) - 1;
	nodo[0].pid = 0;
	nodo[0].h1 = 2*0 + 1;
	nodo[0].h2 = 2*0 + 2; 
	nodo[0].padre = 0;

	
	FILE *f = fopen(nombreArchivo, "rb");
	if (f == NULL) {
		perror("Error al leer archivo");
		exit(EXIT_FAILURE);
	}

	for ( i = 0 ; i < atoi(argc[1]) ; i ++)
	{
		fread(&arr[i],sizeof(int),1,f);
	}
	fclose(f);

	for (i=1; i < m ; i++) {
		nodo[i].padre = (i-1)/2;
		int medio = nodo[nodo[i].padre].fin + nodo[nodo[i].padre].inicio;
		if ( i % 2 == 0) {
			nodo[i].inicio = medio/2;
			nodo[i].fin = nodo[nodo[i].padre].fin;
		}
		else {
		
			nodo[i].inicio = nodo[nodo[i].padre].inicio;
			nodo[i].fin = medio/2-1;
		}
		nodo[i].h1 = 2*i + 1;
		nodo[i].h2 = 2*i + 2;
	}

	if ( n == 1 ) quickSort(arr,nodo[0].inicio, nodo[0].fin); 
	else rama(0);
	
	
	FILE *fwrite = fopen(archivoSalida,"w");
	
	if (fwrite != NULL)
	{
		
		for(int j = 0; j < atoi(argc[1]) ; j++)
			fprintf(fwrite,"%d\n", arr[j]);
			
		fclose(fwrite);
	}
	else printf("Error creando archivo \"%s\" \n", archivoSalida);

	time(&stop);
	printf("Tiempo de Ejecucion: %f \n", difftime(stop, start));
	
	return 0 ; 
}


void rama( int id ) {
	int h = pow(2,n-1)-1;
	
	for (int i = 1 ; i <= 2 ; i++){
		if ( 2*id + i < h ) {
				if (pthread_create( &nodo[2*id + i].pid, NULL, rama, 2*id+i) ) {
					perror("Error al crear thread\n");
					exit(1);
				}		
			}
		else {
			if (pthread_create( &nodo[2*id + i].pid, NULL, hoja, 2*id+i) ) {
				perror("Error al crear thread\n");
				exit(1);
			}	
		}
	}
	pthread_join(nodo[nodo[id].h1].pid, NULL);
	pthread_join(nodo[nodo[id].h2].pid, NULL);
	int n1 = nodo[nodo[id].h1].fin - nodo[nodo[id].h1].inicio +1;
	int n2 = nodo[nodo[id].h2].fin - nodo[nodo[id].h2].inicio +1;
	int j  = 0;
	int k  = n1;

	int arr1[n1+n2];
	for (int i = 0 ; i < n1+n2 ; i ++){
		arr1[i] = arr[nodo[id].inicio+i]; 
	}

	for (int i = 0 ; i < n1+n2 ; i++){
		if ( j == n1 ) {
			arr[nodo[id].inicio+i] = arr1[k++];
		}
		else if ( k == n2+n1) {
			arr[nodo[id].inicio+i] = arr1[j++];
		}
		else if( arr1[j] < arr1[k] ) {
			arr[nodo[id].inicio+i] = arr1[j++];
		}
		else{
			arr[nodo[id].inicio+i] = arr1[k++];
		}
	}
	if ( id != 0 ) {
		pthread_exit(NULL);
	}
}

void hoja (int id) {
	quickSort( arr, nodo[id].inicio, nodo[id].fin );	
	pthread_exit(NULL);	
}

void quickSort(int arr[],int inicio,int fin) {

	if (inicio==fin) return;
    int i,f,temp,pivote;
    i = inicio;
    f = fin;
    pivote = arr[(i+f)/2];
    do{
        while(arr[i]<pivote && i<fin) i++;
        while(pivote<arr[f] && f > inicio) f--;
        if(i <= f)
        {
            temp= arr[i];
            arr[i]=arr[f];
            arr[f]=temp;
            i++;
            f--;
        }
    }while(i<=f);
    if(inicio < i) quickSort(arr,inicio,f);
    if(fin > f) quickSort(arr,i,fin);

}



