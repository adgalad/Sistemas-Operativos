#include "funciones.h"

int main(int argv, char **argc)
{
	int inicio = atoi(argc[1]);
	int n      = atoi(argc[2]) - atoi(argc[1]);
	int *arreglo = readBinaryFile(argc[3],inicio,n);
	
	quickSort(arreglo,0,n-1);
	writeFile(itos(getpid()), arreglo, n, 0); 

	return 0;
}
