/* Pila Creada para motivos de Practica en C
 * Representa el TAD pila
 * Autor: Jose Pena
 */

#ifndef pila_h
#define pila_h
#include "moneda.h"

/* Tipo Nodo */
typedef struct Nodo {

	Moneda m;
	struct Nodo *sig;

}Nodo;

/* Tipo Pila */
typedef struct {

	Nodo *cabeza;

}Pila;

Pila Crear_pila();
/* PRE: True */

/* POST: Pila p vacia */

void Empilar(Pila *p, Moneda m);
/* PRE: Existe pila */

/* POST: Se empila m en p */

Moneda Desempilar(Pila *p);
/* PRE: Existe pila y pila no vacia */

/* POST: Se desempila m de p */

Moneda Tope(Pila *p);
/* PRE: Existe pila y pila no vacia */

/* POST: Se muestra la moneda en el tope de la pila */

void Vaciar(Pila *p);
/* PRE: Existe pila */

/* POST: p esta vacia */ 


#endif 





