
#ifndef ordenArchivoh_h
#define ordenArchivoh_h


typedef struct Nodo_t
{
	int inicio;
	int fin;
	int h1,h2,padre;
	pthread_t pid;
} Nodo;

void hoja (int id);

void rama( int id );

void quickSort(int arr[],int inicio,int fin);

#endif
