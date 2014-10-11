
#include "archivo.h"


char *itos(int n)
{
	char *str = malloc (10);
	int i = 9;
	while(n > 0 && i >= 0)
	{
		str[i--] = n%10 + 48;
		n /= 10;
	}
	if (i == -1 && n > 0) return NULL;
	return (str+i+1);
}

int *readFile(char *fileName, int *n)
{
	
	FILE *fread;
	fread = fopen(fileName,"r");
	int *arr, i;
	if ( fread != NULL )
	{
		
		fscanf(fread,"%d\n",n);
		arr = (int*) malloc(sizeof(int)*(*n));
		for(i = 0; i < (*n) ; i++)
			fscanf(fread,"%d\n", &arr[i]);
		fclose(fread);	
		return arr;
	}
	else printf("Error leyendo archivo \"%s\" \n", fileName);
	return NULL;
}

void writeFile(char *fileName,int *arr, int inicio, int fin)
{
	FILE *fwrite = fopen(fileName,"w");
	int j;
	if (fwrite != NULL)
	{
		fprintf(fwrite,"%d\n",fin-inicio);
		for(j = inicio; j< fin ; j++)
			fprintf(fwrite,"%d\n", arr[j]);
		fclose(fwrite);
	}
	else printf("Error creando archivo \"%s\" \n", fileName);
}

