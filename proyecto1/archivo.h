#include <stdlib.h>
#include <stdio.h>

#ifndef ARCHIVO_H
#define ARCHIVO_H

char *itos(int n);

int *readFile(char *fileName, int *n);

void writeFile(char *fileName,int *arr, int inicio, int fin);

#endif
