
#include "funciones.h"


char *itos(int n)
{
	char *str = malloc (11);
	str[10] = '\0';
	int i = 9;
	while(n > 0 && i >= 0)
	{
		str[i--] = n%10 + 48;
		n /= 10;
	}
	if (i == -1 && n > 0) return NULL;
	return (str+i+1);
}

int *readFile(char *nombreArchivo, int *n)
{
	if (n == 0) return NULL;
	FILE *fread;
	fread = fopen(nombreArchivo,"r");
	int *arreglo, i;
	if ( fread != NULL )
	{
		
		fscanf(fread,"%d\n",n);
		arreglo = (int*) malloc(sizeof(int)*(*n));
		for(i = 0; i < (*n) ; i++)
			fscanf(fread,"%d\n", &arreglo[i]);
		fclose(fread);	
		return arreglo;
	}
	else printf("Error leyendo archivo \"%s\" \n", nombreArchivo);
	return NULL;
}

void writeFile(char *nombreArchivo,int *arreglo, int n, int flag)
{
	FILE *fwrite = fopen(nombreArchivo,"w");
	int j;
	
	if (fwrite != NULL)
	{
		if (!flag) fprintf(fwrite,"%d\n",n);
		
		for(j = 0; j < n ; j++)
			fprintf(fwrite,"%d\n", arreglo[j]);
			
		fclose(fwrite);
	}
	else printf("Error creando archivo \"%s\" \n", nombreArchivo);
}

int *readBinaryFile(char *nombreArchivo, int inicio, int n)
{
	FILE *f = fopen(nombreArchivo, "rb");
	int *arreglo = (int*)malloc(sizeof(int)*n);
	int i;
	
	if (inicio!=0)	fseek(f,sizeof(int)*inicio,SEEK_SET);

	for ( i = 0 ; i < n ; i ++)
	{
		fread(&arreglo[i],sizeof(int),1,f);
	}
	return arreglo;
}

void quickSort(int arreglo[],int inicio,int fin)
{
	if (inicio==fin) return;
    int i,f,temp,pivote;
    i = inicio;
    f = fin;
    pivote = arreglo[(i+f)/2];
    do{
        while(arreglo[i]<pivote && i<fin) i++;
        while(pivote<arreglo[f] && f > inicio) f--;
        if(i <= f)
        {
            temp = arreglo[i];
            arreglo[i] = arreglo[f];
            arreglo[f] = temp;
            i++;
            f--;
        }
    }while(i<=f);
    if(inicio < i) quickSort(arreglo,inicio,f);
    if(fin > f) quickSort(arreglo,i,fin);
}

int* merge(int *arreglo1, int *arreglo2, int n1, int n2)
{
		int j = 0; 
		int k = 0;
		int i = 0;	

	int 	*arreglo = (int*) malloc(sizeof(int)*(n1+n2));
	/*printf("\nAPARTIR DE AQUI:\n");
	for ( j = 0 ; j < n1 ; j ++) printf("%d, ",arreglo1[j]);
	printf("\n");
	for ( j = 0 ; j < n2 ; j ++) printf("%d, ",arreglo2[j]);
	printf("\n\n");*/
		j = 0;
		for (i = 0 ; i < n1+n2 ; i++)
		{
			if (j == n1)
				arreglo[i] = arreglo2[k++];
			else if ( k == n2)
				arreglo[i] = arreglo1[j++];
			else if (arreglo1[j] < arreglo2[k])
				arreglo[i] = arreglo1[j++];
			else 
				arreglo[i] = arreglo2[k++];
		}

	return arreglo;
}

