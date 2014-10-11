#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "archivo.h"



int main(int argv, char **argc)
{
	int arr[] = {5,9,13,7,1,12,15,2,4,3,6,8,10,14,11,18,16,17};
	char *str;
	int n1, n2, j, k, m, i;
	int inicio  = 0, 
		fin     = atoi(argc[1]),
		nivelac = 1, 
		n       = atoi(argc[2]),
		medio;
/*
	FILE *file = fopen(argc[3], "rb");
	if (file == NULL)
	{
		perror("No se pudo abrir el archivo\n");
		return -1;
	}
	fread(arr,4,atoi(argc[1]),file);
*/
	pid_t child;
	if ((child= fork()) == -1){
		perror("Error al crear nuevo proceso");
		exit(EXIT_FAILURE);
	}
	if (child != 0)
	{
		wait(NULL);
		return 0;
	}
 
	
	etiqueta1:if ( nivelac < n )
	{

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
					inicio = medio;			
				else 
					fin = medio;
				goto etiqueta1;
			}			
		}
		int status1,status2;
		pid_t child1 = wait(NULL);
		pid_t child2 = wait(NULL);

		int *arr1, *arr2;
		str = itos(child1);
		arr1 = readFile(str,&n1);	
		remove(str);
	
		str = itos(child2);
		arr2 = readFile(str,&n2);
		remove(str);
		j = 0; 
		k = 0;
		m = 0;	
		
		while (j < n1 || k < n2)
		{
			if (j == n1)
				arr[inicio+m++] = arr2[k++];
			else if ( k == n2)
				arr[inicio+m++] = arr1[j++];
			else if (arr1[j] < arr2[k])
				arr[inicio+m++] = arr1[j++];
			else 
				arr[inicio+m++] = arr2[k++];
		}
		str = itos(getpid());
		writeFile(str,arr,inicio,fin);
		if (nivelac == 1)
		{
			for(j = 0; j < fin ; j++)
				printf("%d ",arr[j]);
			printf("\n");
		}
		exit(1);
	}
	else 
	{
		int j,k;
			
		for (k = inicio; k < fin ; k++)  
			for (j = inicio; j < fin-1; j++)
			{
				if ( arr[j] > arr[j+1] )
				{
					int aux  = arr[j];
					arr[j]   = arr[j+1];
					arr[j+1] = aux;
				}
			}
		
		char *str = itos(getpid());
		writeFile(str,arr,inicio,fin);
		exit(EXIT_SUCCESS);
	}
	
	
	return 0;
}
