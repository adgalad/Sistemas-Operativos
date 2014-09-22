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

void Encolar ( cola *c, archivo *archi ) {
	if ( c->primero == NULL ) {
		nodo *n = (nodo*)malloc(sizeof(nodo));
		n->contenido = archi;
		n->sig = NULL;
		c->primero = n;
		c->ultimo = n;
	}
	else {
		nodo *n = (nodo*)malloc(sizeof(nodo));
		n->contenido = archi;
		n->sig = NULL;
		c->ultimo->sig = n;
		c->ultimo = n;

	}

}

void Desencolar ( cola *c, archivo **archi ){
	if ( c->primero == NULL ) {
		printf("La cola esta vacia\n");
		exit(1);
	}
	else {
		if ( strcmp( c->primero->contenido->nombre, c->ultimo->contenido->nombre ) == 0 ) {
			nodo *aux1;
			*archi = c->primero->contenido;
			aux1 = c->primero;
			aux1->contenido = NULL;
			free(aux1);			// Este es el free que esta jodiendo 
			c->primero = NULL;
			c->ultimo = NULL;
		}
		else {
			nodo *aux1;
			*archi = c->primero->contenido;
			aux1 = c->primero;
			c->primero = c->primero->sig;
			free(aux1);
		

		}
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