
#include "funciones.h"



int main(int argv, char **argc)
{
	char *nombreArchivo = argc[3];
	int   inicio        = 0; 
	int   fin           = atoi(argc[1]);
	int   nivelActual   = 1;
	int 	  nivel         = atoi(argc[2]);
	int   medio;
	int   i;
	pid_t child;
	clock_t start, stop;

	start = clock();
	
	if (nivel <= 0)
	{
		perror("El numero de niveles debe ser mayor que 0");
		exit(EXIT_FAILURE);
	}
	else if (pow(2,nivel-1) > fin)
	{
		perror("El numero de hojas debe ser menor que el numero de enteros");
		exit(EXIT_FAILURE);	
	}
et1:	medio = (fin + inicio)/2;
	for(i = 0; i< 2 ; i++)
	{
		if ((child = fork()) == -1){
			perror("Error al crear nuevo proceso");
			exit(EXIT_FAILURE);
		}
		if (child == 0)
		{	
			nivelActual++;	
			if (i)
				if ((fin - inicio % 2) != 0 ) inicio = medio+1;
				else    inicio = medio;			
			else 
				if ((fin - inicio % 2) != 0 ) fin = medio+1;
				else    fin = medio;		
			if (nivelActual < nivel)
			{	
				goto et1;
			}
			else
			{
//				chdir("./");
				char app[] = "./hoja";
        			char *const argv[] = { app, itos(inicio), itos(fin),
        			                       nombreArchivo,  NULL };
        			
        			if (execv(app, argv) < 0)
				{
					perror("Error al llamar a execl");
					exit(EXIT_FAILURE);
				}
			}	
		}			
	}

	int *arreglo, *aux1, *aux2;
	int n1,n2;
	
	child = wait(NULL);
	nombreArchivo = itos(child);
	aux1 = readFile(nombreArchivo,&n1);
	remove(nombreArchivo);

	child = wait(NULL);
	nombreArchivo = itos(child);
	aux2 = readFile(nombreArchivo,&n2);
	remove(nombreArchivo);
	int j;	
	
	arreglo = merge(aux1,aux2,n1,n2);
	
	if (nivelActual == 1)
	{ 
		writeFile("ArchivoEnterosOrdenado",arreglo,n1+n2,1);
		stop = clock();
		printf("Tardo %.6f segundos \n",(double)(stop-start)/CLOCKS_PER_SEC);
	}
	else                  writeFile(itos(getpid()),arreglo,n1+n2,0);

	free(aux1);
	free(aux2);
	free(arreglo);
	exit(EXIT_SUCCESS);
}
	
