#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include "hojah.h"
#include "ordenArchivo-h.h"


int main ( int argv, char **argc ) {
        printf("sapoteton\n");
		int inicio = atoi(argc[1]);
		int fin = atoi(argc[1]);
        //extern int arr[];
		//quickSort(arr,inicio,fin);
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