

#include "Estacionamiento.h"




int main()
{
    char *archivoFuente = malloc(sizeof(char) * 1024);
    
    int capacidad;
    printf("Introduzca la capacidad que tendra cada piso del estacionamiento\n");
    scanf("%d",&capacidad);
    printf("Introduzca el nombre del archivo de entrada \n");
    scanf("%s",archivoFuente);
    
    ProcesarLLegadas(archivoFuente,capacidad);
    
    return 0;
}
