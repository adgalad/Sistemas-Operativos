#include "funciones.h"

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