#include <stdio.h>
#include <pthread,h>
#include <unistd.h>
#include <math.h>
#include "archivo.h"

typedef struct Nodo_t
{
	int inicio;
	int fin;
	int h1,h2,padre;
	pthread_t pid;
} Nodo;


int *arr	; 
Nodo nodo[pow(2,n)-1];

void rama(int id)
{
	pthread_join(nodo[nodo[id].h1].pid, NULL);
	pthread_join(nodo[nodo[id].h2].pid, NULL);
	int i,
		j = nodo[nodo[id].h1].inicio,
		k = nodo[nodo[id].h2].inicio,
		n1 = nodo[nodo[id].h1].fin - j,
		n2 = nodo[nodo[id].h2].fin - k;
		  
	int arr1[nodo[i].fin - nodo[i].inicio];
	for (i = 0 ; i < nodo[id].fin - nodo[id].inicio; i++)
	{
		arr1[i] = arr[nodo[id].inicio+i];
	}
	for ( i = nodo[id].inicio ; i < nodo[id].fin ; i++)
	{
			if (j == n1 )
				arr[nodo[id].inicio+i] = arr1[k++];
			else if ( k == n2)
				arr[nodo[id].inicio+i] = arr1[j++];
			else if (arr1[j] < arr1[k])
				arr[nodo[id].inicio+i] = arr1[j++];
			else 
				arr[nodo[id].inicio+i] = arr1[k++];
	} 
	pthread_exit(NULL);
}

int main(int argv, char **argc)
{
	int  n = argc[2];
	int i;	
	nodo[0].inicio = 0;
	nodo[0].fin = argc[1];
	nodo[0].pid = 0; 
	for (i=1, i < pow(2,n)-1 ; i++
	{
		nodo[i].padre = (i-1)/2;
		int medio = nodo[nodo[i].padre].inicio - nodo[nodo[i].padre].fin;
		if ( i % 2 == 0) 
		{
			if (medio % 2 == 0) medio /= 2;
			else                medio = medio/2 +1;
			nodo[i].inicio = medio;
			nodo[i].fin = nodo[nodo[i].padre].fin;
		}
		else 
		{
			nodo[i].inicio = nodo[nodo[i].padre].inicio;
			nodo[i].fin = medio/2;
		}
		nodo[i].h1 = 2*i + 1;
		nodo[i].h2 = 2*i + 2;

		if ( i < pow(2,n-1) - 1 )
		{
			if (pthread_create( &nodo[i].pid, NULL, NULL, NULL)
			{
				perror("Error al crear thread\n");
				exit(EXIT_FAILURE);
			}		
		}
		else
		{
			if (pthread_create( &nodo[i].pid, NULL, 
					execlp("hojah","hojah",fin - medio,str)	, NULL)
			{
				perror("Error al crear thread\n");
				exit(EXIT_FAILURE);
			}	
		}
			
		}
	}
	
	/*leer archivo */
	
	
	
	return 0 ; 
}
