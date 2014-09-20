
#include "Vehiculo.h"


void SetLongitud(Vehiculo *v, float longitud)
{
    v->longitud = longitud;
}

void SetPlaca (Vehiculo *v, char *placa)
{
    v->placa = placa;
}
void SetModelo (Vehiculo *v, char *modelo)
{
    v->modelo = modelo;
}
void SetAnio (Vehiculo *v, int anio)
{
    v->anio = anio;
}
void SetColor (Vehiculo *v, char* color)
{
    v->color = color;
}

float GetLongitud (Vehiculo v)
{
    return v.longitud;
}

char* GetPlaca (Vehiculo v)
{
    return v.placa;
}

char* GetModelo(Vehiculo v)
{
    return v.modelo;
}

int GetAnio(Vehiculo v)
{
    return v.anio;
}

char* GetColor(Vehiculo v)
{
    return v.color;
}

Vehiculo Crear_V(float l, char* p, char* m, int a, char* c)
{
    Vehiculo v;
    SetLongitud(&v, l);
    SetPlaca(&v, p);
    SetModelo(&v, m);
    SetAnio(&v, a);
    SetColor(&v, c);
    return v;
}

void Destruir_V(Vehiculo *v)
{
    SetLongitud(v, 0);
    SetPlaca(v, NULL);
    SetModelo(v, NULL);
    SetAnio(v, 0);
    SetColor(v, NULL);
}