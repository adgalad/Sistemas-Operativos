#include <stdlib.h>
#include <stdio.h>

#ifndef ARCHIVO_H
#define ARCHIVO_H

char *itos(int n);

int *readFile(char *fileName, int *n);

void writeFile(char *fileName,int *arr, int inicio, int fin);

void quickSort(int arr[],int inicio,int fin);

void merge(int *arr, int *arr1, int *arr2, int inicio, int n1, int n2);

#endif
