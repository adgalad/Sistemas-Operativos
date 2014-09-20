

#ifndef Piso_h
#define Piso_h

#include "Vehiculo.h"


/* Tipo Nodo Vehiculo */
typedef struct NodoVehiculo_T
{
    Vehiculo v;
    struct NodoVehiculo_T *sig;
    
}NodoVehiculo;

/* Tipo Pila de Vehiculos */
typedef struct
{
    NodoVehiculo *primero;
    
}PilaVehiculo;


void Empilar(PilaVehiculo *pila,Vehiculo v);
/* PRE: Existe pila */

/* POST: Se empila v en pila */

Vehiculo Desempilar(PilaVehiculo *pila);
/* PRE: la pila no puede estar vacia */

/* POST: se desempila un vehiculo de pila */


/* Tipo Piso */
typedef struct
{
    PilaVehiculo pila;
    int capacidad;
    int ocupacion;
    
}Piso;

void SetOcupacion(Piso *p,int nuevaOcupacion);
/* PRE: True */

/* POST: p.ocupacion = nuevaOcupacion */

int GetOcupacion(Piso p);
/* PRE: True */

/* POST: Retorna p.ocupacion */

int GetCapacidad(Piso p);
/* PRE: True */

/* POST: Retorna p.capacidad */

Piso Crear_P(int capacidad);
/* PRE: True */

/* POST: se crea una piso p y p.capacidad = capacidad */

void Destruir_P(Piso *p, char *archivoTraza);
/* PRE: Existe p */

/* PRE: Destruye p */

void Estacionar_P(Piso *p, Vehiculo v);
/* PRE: Existe p.pilaVehiculo y p.ocupacion < p.capacidad */

/* POST: Se estaciona v en p y aumenta p.ocupacion en 1 */

Vehiculo Retirar_P(Piso *p);
/* PRE:  Existe p.pilaVehiculo y p.ocupacion > 0 */

/* POST: Retira el ultimo vehiculo estacionado en p y decrementa p.ocupacion en 1 */

Vehiculo Cercano_P(Piso p);
/* PRE:  Existe p.pilaVehiculo y p.ocupacion > 0 */

/* POST: Devuelve el ultimo vehiculo estacionado en p */

boolean Cabe_P(Piso p);
/* PRE:  Existe p.pilaVehiculo */

/* POST: Devuelve ( p.ocupacion < p.capacidad ) */

#endif
