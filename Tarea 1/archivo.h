/* Tarea 1 
 * Representa el TAD archivo
 * Autor: 
 */

#ifndef archivo_h
#define archivo_h

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct archivo {
	char *nombre;
	bool tipo;
	int	numarchi;
	struct archivo *sig;
	struct archivo *hijo;

}archivo;

void Llegar_ruta( archivo **raiz, char **tokken );
/* PRE: La ruta debe existir */

/* POST: El apuntador se encuentra apuntando a la direccion de la ruta */

void Crear_archivo( archivo **raiz, char **tokken );
/* PRE: La ruta debe existir */

/* POST: Se ha creado el archivo en la ruta */

void Crear_directorio( archivo **raiz, char **tokken );
/* PRE: La ruta debe existir */

/* POST: Se ha creado el archivo en la ruta */

void Listar_archivos( archivo **raiz, char **tokken );
/* PRE: La ruta debe existir */

/* POST: Se imprime por salida estandar 
 * los archivos o directorios de la  ruta */

void Eliminar_archivos( archivo **raiz, char **tokken );
/* PRE: El archivo debe existir en la ruta o El directorio debe existir
 * en la ruta y debe estar vacio */

/* POST: Se ha eliminado el archivo o directorio */


#endif 
