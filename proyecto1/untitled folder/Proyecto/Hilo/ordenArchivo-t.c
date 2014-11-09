
/*  Proyecto 1: Hilos
 *
 *	Autor: Carlos Spaggiari 11-10987
 *		   Jose Peña 	    11-10775       
*/

#include "funciones.h"

int main(int argv, char **argc) {

	if (argv < 5) {
		perror("Faltan argumentos");
		exit(1);
	}
	
	clock_t start, stop;

	start = clock();

	n = atoi(argc[2]);
	int i;
	char *nombreArchivo = argc[3];
	char *archivoSalida = argc[4];

	else if ( n <= 0 ) {
		perror( "El numero de niveles debe ser mayor que 0");
		exit(1);
	}
	else if ( pow(2,n-1) > atoi(argc[1]) ) {
		perror("El numero de hilos no puede ser mayor al numero de enteros ");
		exit(1);
	}


	int m = pow(2,n)-1;
	FILE *fp;
	arr  = (int *) malloc(sizeof(int)*atoi(argc[1]));
	nodo = (Nodo*) malloc(sizeof(Nodo)*pow(2,n-1));
	nodo[0].inicio = 0;
	nodo[0].fin = atoi(argc[1]) - 1;
	nodo[0].pid = 0;
	nodo[0].h1 = 2*0 + 1;
	nodo[0].h2 = 2*0 + 2; 
	nodo[0].padre = 0;

	
	FILE *f = fopen(nombreArchivo, "rb");
	if (f == NULL) {
		perror("Error al leer archivo");
		exit(EXIT_FAILURE);
	}

	for ( i = 0 ; i < atoi(argc[1]) ; i ++)
	{
		fread(&arr[i],sizeof(int),1,f);
	}
	fclose(f);

	for (i=1; i < m ; i++) {
		nodo[i].padre = (i-1)/2;
		int medio = nodo[nodo[i].padre].fin + nodo[nodo[i].padre].inicio;
		if ( i % 2 == 0) {
			nodo[i].inicio = medio/2;
			nodo[i].fin = nodo[nodo[i].padre].fin;
		}
		else {
		
			nodo[i].inicio = nodo[nodo[i].padre].inicio;
			nodo[i].fin = medio/2-1;
		}
		nodo[i].h1 = 2*i + 1;
		nodo[i].h2 = 2*i + 2;
	}

	if ( n == 1 ) quickSort(arr,nodo[0].inicio, nodo[0].fin); 
	else rama(0);
	
	
	FILE *fwrite = fopen(archivoSalida,"w");
	
	if (fwrite != NULL)
	{
		
		for(int j = 0; j < atoi(argc[1]) ; j++)
			fprintf(fwrite,"%d\n", arr[j]);
			
		fclose(fwrite);
	}
	else printf("Error creando archivo \"%s\" \n", archivoSalida);

	stop = clock();
	printf("Tiempo de Ejecucion: %6f \n", (double) (stop - start)/CLOCKS_PER_SEC );

	free(nodo);
	free(arr);
	
	return 0 ; 
}






