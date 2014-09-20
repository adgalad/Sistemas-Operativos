/* Pila Creada para motivos de Practica en C
 * TAD Pila
 * Autor: Jose Pena
 */

#include "pila.h"
#include <stdlib.h>
#include <stdio.h>

 Pila Crear_pila() {

 	Pila p;

 	return p;

 }

 void Empilar( Pila *p, Moneda m ) {
 	if ( p->cabeza == NULL ) {
 		Nodo *n = malloc(sizeof(Nodo));
 		n->m = m;
 		n->sig = NULL;
 		p->cabeza = n;
 	}

 	else {
 		Nodo *n = malloc(sizeof(Nodo));
 		n->m = m;
 		n->sig = p->cabeza;
 		p->cabeza = n;

 	}

 }

 Moneda Tope( Pila *p ) {
 	if ( p->cabeza == NULL ) {
 		printf(" La pila esta vacia, saliendo del programa con errores\n ");
 		exit(1);
 	}
 	else {
 		Moneda m;
 		m.valor = p->cabeza->m.valor;
 		m.divisa = p->cabeza->m.divisa;
 		return m;
 	}

 }

 Moneda Desempilar( Pila *p ) {
 	if ( p->cabeza == NULL ) {
 		printf(" La pila esta vacia, saliendo del programa con errores\n ");
 		exit(1);
 	}
 	else {
 		Nodo *aux = malloc(sizeof(Nodo));
 		Moneda m;
 		aux = p->cabeza;
 		p->cabeza = p->cabeza->sig;
 		m = aux->m;
 		free(aux);
 		return m;

 	}
 }

 void Vaciar ( Pila *p ) {
 	if ( p->cabeza == NULL ) {
 	}
 	else {

 		while ( p->cabeza != NULL ) {
 			Nodo *aux = malloc(sizeof(Nodo));
 			aux = p->cabeza;
 			p->cabeza = p->cabeza->sig;
 			free(aux);
 		}
 	}

 }