


#ifndef Estacionamiento_h
#define Estacionamiento_h

#include "Piso.h"

/* Tipo Nodo Piso */
typedef struct NodoPiso_T
{
    Piso p;
    struct NodoPiso_T *sig;
    
}NodoPiso;

/* Tipo Pila de Vehiculos */
typedef struct
{
    NodoPiso *primero;
    NodoPiso *ultimo;
    
}ColaPiso;

void Encolar(ColaPiso *cola,Piso p);
/* PRE: Existe cola */

/* POST: Se encola p en cola */

Piso Desencolar(ColaPiso *cola);
/* PRE: cola no puede estar vacia */

/* POST: se desencola el primer piso de la cola */



/* Tipo Estacionamiento */
typedef struct
{
    ColaPiso cola;
    int numPisos;
    
}Estacionamiento;


void SetNumPisos(Estacionamiento *e,int numPisos);
/* PRE: True */

/* POST: e.numPisos = numPisos */

int GetNumPisos(Estacionamiento e);
/* PRE: True */

/* POST: retorna el numero de pisos en e */

boolean Estacionar_E(Estacionamiento *e, Vehiculo v,char* archivoTraza,int capacidad);
/* PRE: Existe e */

/* POST: Estaciona v en e y devuelve true o false si logra estacionar o no respectivamente*/

Vehiculo Retirar_E(Estacionamiento *e);
/* PRE: existe e */

/* POST: devuelve el ultimo vehiculo estacionado del primer piso del estacionamiento   */

Estacionamiento Generar_E();
/* PRE: true */

/* POST: crea un estacionamiento e */


void Destruir_E(Estacionamiento *e,char* archivoTraza);
/* PRE: existe e */

/* POST: destruye e */


void Vaciar_E(Estacionamiento *e,char* archivoTraza);
/* PRE: existe e */

/* POST: vacia los pisos en e.ColaPiso */

void ProcesarLLegadas(char *archivoFuente, int capacidad);
/* PRE: True */

/* POST: lee un archivo de entrada, procesa su informacion y escribe un archivo de traza */


#endif

