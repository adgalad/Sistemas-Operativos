/* Pila Creada para motivos de Practica en C
 * Representa el TAD Moneda
 * Autor: Jose Pena
 */

#ifndef moneda_h
#define moneda_h

/* Tipo Moneda */
typedef struct {

	int valor;
	char *divisa; 

}Moneda;


Moneda Crear_moneda(int valor, char *divisa);
/* PRE: True */

/* POST: m es una moneda */

#endif

