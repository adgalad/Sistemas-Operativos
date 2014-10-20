
#ifndef ordenArchivoh_h
#define ordenArchivoh_h


typedef struct Nodo_t
{
	int inicio;
	int fin;
	int h1,h2,padre;
	pthread_t pid;
} Nodo;

typedef struct Arg_t {
	int id;
	Nodo *nodo; 
	int *arr;
} Arg_t;

void hoja (Arg_t *argumento);

void rama( Arg_t *argumento );

void quickSort(int arr[],int inicio,int fin);

#endif