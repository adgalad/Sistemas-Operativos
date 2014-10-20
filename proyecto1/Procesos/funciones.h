#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#ifndef ARCHIVO_H
#define ARCHIVO_H

char *itos(int n);

int *readFile(char *nombreArchivo, int *n);

void writeFile(char *nombreArchivo,int *arr, int n, int flag);

int *readBinaryFile(char *nombreArchivo, int inicio, int n);

void quickSort(int arr[],int inicio,int fin);

int* merge(int *arreglo1, int *arreglo2, int n1, int n2);

#endif
