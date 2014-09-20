

#ifndef Vehiculo_h
#define Vehiculo_h


#include <stdio.h>
#include <stdlib.h>

/* Tipo Boolean */
typedef enum
{
    false = 0,
    true = 1
}boolean;


/* Tipo Vehiculo */
typedef struct
{
    float   longitud;
    char    *placa;
    char    *modelo;
    int     anio;
    char    *color;
    
}Vehiculo;



void SetLongitud(Vehiculo *v, float longitud);
/* PRE: TRUE */
/* POST: v.longitud = longitud */

void SetPlaca (Vehiculo *v, char *placa);
/* PRE: TRUE */
/* POST: v.placa = placa */

void SetModelo (Vehiculo *v, char *modelo);
/* PRE: TRUE */
/* POST: v.modelo = modelo */

void SetAnio (Vehiculo *v, int anio);
/* PRE: TRUE */
/* POST: v.anio = anio */

void SetColor (Vehiculo *v, char* color);
/* PRE: TRUE */
/* POST: v.color = color */


float GetLongitud (Vehiculo v);
/* PRE: TRUE */
/* POST: retorna v.longitud */

char* GetPlaca (Vehiculo v);
/* PRE: TRUE */
/* POST: retorna v.placa */

char* GetModelo(Vehiculo v);
/* PRE: TRUE */
/* POST: retorna v.modelo */

int GetAnio(Vehiculo v);
/* PRE: TRUE */
/* POST: retorna v.anio */

char* GetColor(Vehiculo v);
/* PRE: TRUE */
/* POST: retorna v.color */

Vehiculo Crear_V(float l, char* p, char* m, int a, char* c);
/* PRE: True */

/* POST: Retorna un vehiculo con sus respectivos atributos */

void Destruir_V(Vehiculo *v);
/* PRE: True */

/* POST: Destruye el vehiculo */

#endif
