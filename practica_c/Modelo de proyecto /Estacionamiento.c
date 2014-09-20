

#include "Estacionamiento.h"

void Encolar(ColaPiso *cola,Piso p)
{
    
    NodoPiso *np = malloc(sizeof(NodoPiso));
    np->p = p;
    np->sig = NULL;
    if (cola->primero == NULL)
        {
        cola->primero = np;
        cola->ultimo = np;
        }
    else
        {
        cola->ultimo->sig = np;
        cola->ultimo = np;
        }
}

Piso Desencolar(ColaPiso *cola)
{
    Piso p;
    p = cola->primero->p;
    cola->primero = cola->primero->sig;
    return p;
}



void SetNumPisos(Estacionamiento *e,int numPisos)
{
    e->numPisos = numPisos;
}

int GetNumPisos(Estacionamiento e)
{
    return e.numPisos;
}

void imprimir(Piso p)
{
    NodoVehiculo *nv = p.pila.primero;
    for (int i = 0;i< p.ocupacion ; i++)
        {
        printf("%s \n",nv->v.placa);
        nv = nv->sig;
        }
}

boolean Estacionar_E(Estacionamiento *e, Vehiculo v,char* archivoTraza,int capacidad)
{
    FILE *traza = fopen(archivoTraza, "a");
    fprintf(traza, "\nP %s\t%0.1f\t%s\t%d\t%s\n",v.placa,v.longitud,v.modelo,v.anio,v.color);
    fprintf(traza, "--> Entra Vehiculo %s de longitud %f\n",v.placa,v.longitud);
    
    
    
    
    if (e->cola.primero == 0)
        {
        fprintf(traza, "--> No existe Piso disponible\n");
        fprintf(traza, "--> Se crea Piso de capacidad %d y ocupacion 0\n",capacidad);
        Encolar(&e->cola, Crear_P(capacidad));
        SetNumPisos(e, GetNumPisos(*e)+1);
        Estacionar_P(&e->cola.ultimo->p, v);
        fprintf(traza, "--> Se Estaciona Vehiculo %s en Piso (ocupacion %d)\n",v.placa, GetOcupacion(e->cola.ultimo->p));
        }
    else if (Cabe_P(e->cola.ultimo->p))
        {
        Estacionar_P(&e->cola.ultimo->p, v);
        fprintf(traza, "--> Se Estaciona Vehiculo %s en Piso (ocupacion %d)\n",v.placa, GetOcupacion(e->cola.ultimo->p));
        
        }
    else if (!Cabe_P(e->cola.ultimo->p))
        {
        
        fprintf(traza,"--> Capacidad Piso Excedida\n");
        fprintf(traza,"--> Se coloca Piso de ultimo en la cola de Pisos de Tolon_Andromeda\n");
        fprintf(traza,"--> Se crea Piso de capacidad %d y ocupacion 0\n",capacidad);
        Encolar(&e->cola, Crear_P(capacidad));
        SetNumPisos(e, GetNumPisos(*e)+1);
        Estacionar_P(&e->cola.ultimo->p, v);
        fprintf(traza, "--> Se Estaciona Vehiculo %s en Piso (ocupacion %d)\n",v.placa, GetOcupacion(e->cola.ultimo->p));
        
        }
    fclose(traza);
    return true;
}




Estacionamiento Crear_E()
{
    Estacionamiento e;
    ColaPiso cola;
    e.numPisos=0;
    e.cola = cola;
    e.cola.primero = NULL;
    e.cola.ultimo  = NULL;
    return e;
}

Vehiculo Retirar_E(Estacionamiento *e)
{
    Vehiculo v;
    v = Retirar_P(&e->cola.primero->p);
    return v;
}

Estacionamiento Generar_E(int capacidad)
{
    Estacionamiento e;
    Encolar(&e.cola, Crear_P(capacidad));
    return e;
}


void Destruir_E(Estacionamiento *e,char* archivoTraza)
{
    Destruir_P(&e->cola.primero->p, archivoTraza);
    Desencolar(&e->cola);
}


void Vaciar_E(Estacionamiento *e,char* archivoTraza)
{
    int i=0;
    for ( i=0; i<GetNumPisos(*e) ; i++)
        {
        FILE *traza = fopen(archivoTraza,"a");
        fprintf(traza, "--> Piso %d\n",i+1);
        fclose(traza);
        Destruir_E(e,archivoTraza);
        }
}

void ProcesarLLegadas(char* nombreArchivo,int capacidad)
{
    FILE *archivo;
    Estacionamiento e;
    archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL)
        {
        printf("Archivo no encontrado, abortando\n");
        return;
        }
    char *archivoTraza =  malloc(sizeof(char) * 1024);
    char comando;
    while (fscanf(archivo, "%c\t",&comando))
        {
        if( comando == 'C')
            {
            fscanf(archivo, "%s\n",archivoTraza);
            e = Crear_E();
            FILE *traza = fopen(archivoTraza,"w");
            fprintf(traza, "C\t%s\n",nombreArchivo);
            fprintf(traza,"--> Se crea Estacionamiento \n");
            fclose(traza);
            }
        else if( comando == 'P')
            {
            
            float   l;
            char    *p = malloc(sizeof(char) * 32);
            char    *m = malloc(sizeof(char) * 32);
            int     a;
            char    *c = malloc(sizeof(char) * 32);
            fscanf(archivo, "%s\t", p);
            fscanf(archivo, "%f\t",&l);
            fscanf(archivo, "%s\t", m);
            fscanf(archivo, "%d\t",&a);
            fscanf(archivo, "%s\t", c);
            Estacionar_E(&e, Crear_V(l, p, m, a, c),archivoTraza,capacidad);
            }
        else if (comando == 'K')
            {
            FILE *traza = fopen(archivoTraza,"a");
            fprintf (traza,"\nK	Bye Bye\n");
            fprintf (traza,"--> Se vacian los pisos en orden\n");
            fclose(traza);
            Vaciar_E(&e,archivoTraza);
            traza = fopen(archivoTraza,"a");
            fprintf(traza,"--> Se destruyen estacionamiento, Pisos y vehiculos remanentes\n");
            fprintf(traza,"--> Adios");
            
            fclose(traza);
            fclose(archivo);
            return;
            }
        }
}
