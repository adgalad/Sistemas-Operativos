/* Tarea 1 
 * Representa el TAD cola
 * Autor: 
 */

 #ifndef cola_h

 #define cola_h
 #include <stdlib.h>
 #include <stdio.h>
 #include <stdbool.h>
 #include <string.h>
 #include "archivo.h"

 typedef struct nodo {
 	archivo *contenido;
 	struct nodo *sig;

 }nodo;

 typedef struct  cola {
 	nodo *primero;
 	nodo *ultimo;
 }cola;

 cola Crear_cola ();
 	/* PRE: True */

 	/* POST: Se crear la cola */

 void Encolar ( cola *c, archivo **archi );
 	/* PRE: Existe cola */

 	/* POST: Se ha agregado un nuevo nodo a la cola */

 archivo* Desencolar ( cola *c );
 	/* PRE: La cola no esta vacia */

 	/* POST: Se desempila el archivo de la cola */

 bool Cola_vacia ( cola c );
 	/* PRE: Existe cola */

 	/* POST: Devuelve True si la cola esta vacia */

#endif
