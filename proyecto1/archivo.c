
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
	if (n == 0) return NULL;
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

void quickSort(int arr[],int inicio,int fin)
{
	if (inicio==fin) return;
    int i,f,temp,pivote;
    i = inicio;
    f = fin;
    pivote = arr[(i+f)/2];
    do{
        while(arr[i]<pivote && i<fin) i++;
        while(pivote<arr[f] && f > inicio) f--;
        if(i <= f)
        {
            temp= arr[i];
            arr[i]=arr[f];
            arr[f]=temp;
            i++;
            f--;
        }
    }while(i<=f);
    if(inicio < i) quickSort(arr,inicio,f);
    if(fin > f) quickSort(arr,i,fin);
}

void merge(int *arr, int *arr1, int *arr2, int inicio, int n1, int n2)
{
		int j = 0, 
			k = 0,
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
}

