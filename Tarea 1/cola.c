/* Tarea 1 
 * TAD cola
 * Autor: 
 */


#include "cola.h"

 cola Crear_cola() {
 	cola c;
 	c.primero = NULL;
 	c.ultimo = NULL;
 	return c;
 }

void Encolar ( cola *c, archivo **archi ) {
	if ( c->primero == NULL ) {
		nodo *n = (nodo*)malloc(sizeof(nodo));
		n->contenido = *archi;
		n->sig = NULL;
		c->primero = n;
		c->ultimo = n;
	}
	else {
		nodo *n = (nodo*)malloc(sizeof(nodo));
		n->contenido = *archi;
		n->sig = NULL;
		c->ultimo->sig = n;
		c->ultimo = n;
	}

}

archivo* Desencolar ( cola *c ){
	if ( c->primero == NULL ) {
		printf("La cola esta vacia\n");
		exit(1);
	}
	else {
		nodo *aux1;
		archivo *aux;
		aux = c->primero->contenido;
		aux1 = c->primero;
		c->primero = c->primero->sig;
		free(aux1);			
		return aux;
		
	}
}

bool Cola_vacia ( cola c ){
	if ( c.primero == NULL ){
		return true;
	}
	else {
		return false;
	}
}