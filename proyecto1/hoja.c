#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "archivo.h"

int main(int argv, char **argc)
{
	int *arr;
	int fin = atoi(argc[1]),i;
	int *n;
	*n = fin;

	arr = readFile(argc[2],n);
	quickSort(arr,0,fin);
	writeFile(argc[2], arr, 0, fin); 

	for(i = 0; i<fin ; i++)
	{
		printf("%d, ",arr[i]);
	}
	printf("\n");

	return 0;
}
