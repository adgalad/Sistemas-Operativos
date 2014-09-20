

#include "Piso.h"


void Empilar(PilaVehiculo *pila,Vehiculo v)
{
    NodoVehiculo *nv = malloc(sizeof(NodoVehiculo));;
    nv->v = v;
    if (pila->primero == NULL)
        {
        pila->primero = nv;
        }
    else
        {
        nv->sig = pila->primero;
        pila->primero = nv;
        }
}

Vehiculo Desempilar(PilaVehiculo *pila)
{
    Vehiculo v;
    v = pila->primero->v;
    pila->primero = pila->primero->sig;
    return v;
}



void SetOcupacion(Piso *p,int nuevaOcupacion)
{
    p->ocupacion = nuevaOcupacion;
}
int GetOcupacion(Piso p)
{
    return p.ocupacion;
}

int GetCapacidad(Piso p)
{
    return p.capacidad;
}

Piso Crear_P(int capacidad)
{
    Piso p;
    PilaVehiculo pila;
    p.pila = pila;
    p.ocupacion = 0;
    p.capacidad = capacidad;
    p.pila.primero = NULL;
    return p;
}

void Estacionar_P(Piso *p, Vehiculo v)
{
    Empilar(&p->pila,v);
    SetOcupacion(p, GetOcupacion(*p)+1);
}

Vehiculo Retirar_P(Piso *p)
{
    Vehiculo v;
    v = Desempilar(&p->pila);
    SetOcupacion(p, GetOcupacion(*p)-1);
    return v;
}

Vehiculo Cercano_P(Piso p)
{
    Vehiculo v;
    v = p.pila.primero->v;
    return v;
}

boolean Cabe_P(Piso p)
{
    return ( GetOcupacion(p) < GetCapacidad(p));
}

void Destruir_P(Piso *p, char* archivoTraza)
{
    FILE *traza = fopen(archivoTraza,"a");
    Vehiculo v;
    int c = GetOcupacion(*p);
    for (int i=0; i<c;i++)
        {
        v = Retirar_P(p);
        fprintf(traza, "<-- Sale Vehiculo %s\n",v.placa);
        }
    fclose(traza);
}