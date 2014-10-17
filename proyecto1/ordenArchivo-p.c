#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "archivo.h"



int main(int argv, char **argc)
{
	int arr[] = {9,5,6,3,88,4,4,5,1,5,18,16,11,17,19,10,25,1}, *arr1, *arr2;
	char *str;
	int n1, n2, i, j;
	int inicio  = 0, 
		fin     = atoi(argc[1]),
		nivelac = 1, 
		n       = atoi(argc[2]),
		medio;
	pid_t child;
/*
	FILE *file = fopen(argc[3], "rb");
	if (file == NULL)
	{
		perror("No se pudo abrir el archivo\n");
		return -1;
	}
	fread(arr,4,atoi(argc[1]),file);
*/	
et1:	if ( nivelac < n )
	{
		int b = 0;
		if ((inicio + fin) % 2 == 0)
			b = 1;
		medio = (inicio + fin)/2;
		for(i = 0; i< 2 ; i++)
		{
			if ((child= fork()) == -1){
				perror("Error al crear nuevo proceso");
				exit(EXIT_FAILURE);
			}
			if (child == 0)
			{	
				nivelac++;	
				if (i)
					if (!b) inicio = medio+1;
					else    inicio = medio;			
				else 
					fin = medio;
				goto et1;
			}			
		}
		child = wait(NULL);
		str = itos(child);
		arr1 = readFile(str,&n1);	
		remove(str);
		
		child = wait(NULL);
		str = itos(child);
		arr2 = readFile(str,&n2);
		remove(str);

		merge(arr,arr1,arr2,inicio,n1,n2);
		free(arr1);
		free(arr2);
		if (nivelac > 1)	
		{
			str = itos(getpid());
			writeFile(str,arr,inicio,fin);
			exit(EXIT_SUCCESS);
		}
	}
	else 
	{
		for(i = 0; i< 2 ; i++)
		{
			if ((child= fork()) == -1){
				perror("Error al crear nuevo proceso");
				exit(EXIT_FAILURE);
			}
			str = itos(getpid());
			writeFile(str,arr,inicio,fin);
			if (child == 0)
			{	
				if (i)			
					execlp("hoja","hoja",fin - medio,str);			
				else 		
					execlp("hoja","hoja",medio - inicio,str);
			}
			
		}
	}
	if (nivelac == 1){
	for(i = 0; i<fin ; i++)
	{
		printf("%d, ",arr[i]);
	}
	printf("\n");
}
	
	return 0;
}
