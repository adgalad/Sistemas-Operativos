#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#ifndef FUNCIONES
#define FUNCIONES

typedef struct Nodo_t
{
	int inicio;
	int fin;
	int h1,h2,padre;
	pthread_t pid;
} Nodo;

Nodo *nodo;
int *arr;
int n;

void hoja (int id);

void rama( int id );

void quickSort(int arr[],int inicio,int fin);


#endif