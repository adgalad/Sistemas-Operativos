/* Pila Creada para motivos de Practica en C
 * TAD Moneda
 * Autor: Jose Pena
 */

#include "moneda.h"

 Moneda Crear_moneda (int valor, char *divisa) {

 	Moneda m;
 	m.valor = valor;
 	m.divisa = divisa;

 	return m;
 }