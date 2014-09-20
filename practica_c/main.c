/* Pila Creada para motivos de Practica en C
 * Main del programa
 * Autor: Jose Pena
 */

 /* Commandos: C = crear pila, E = empilar moneda, 
 			   D desempilar moneda, T = Tope de la pila, 
 			   V = Vaciar pila */




 #include "pila.h"
 #include <stdio.h>
 #include <stdlib.h>


int main (int argc, char **argv ) {

	*argv++;
	FILE *archivo = fopen( *argv, "r");

	if ( archivo == NULL ) {
		printf( "\nArchivo no encontrado\n");
		exit(1);
	}

	FILE *traza = fopen ( "traza.txt", "w");
	char comando;
	Pila p;

	while ( fscanf( archivo, "%c\n", &comando ) ) {
		if ( comando == 'C' ) {
			p = Crear_pila();
			char *primero;
			char *segundo;
			fprintf ( traza, "Se ha creado una pila vacia\n");

		}
		else if ( comando == 'E' ) {
			int valor;
			char *divisa = malloc(sizeof(char) * 3);
			fscanf( archivo, "%d\t", &valor);
			fscanf( archivo, "%s\n", divisa);
			Moneda m = Crear_moneda(valor, divisa);
			Empilar(&p, m);
			fprintf(traza, " Se ha empilado la moneda %d %s \n",valor,divisa);
		}
		else if ( comando == 'T') {
			Moneda m;
			m = Tope(&p);
			fprintf(traza, "El tope de la pila es %d %s\n",m.valor, m.divisa);

		}
		else if ( comando == 'D') {
			Moneda m;
			m = Desempilar(&p);
			fprintf(traza, "Se ha Desempilado la moneda %d %s\n", m.valor, m.divisa );
		}
		else if ( comando == 'V') {
			Vaciar(&p);
			fprintf(traza, "Se ha vaciado la pila completamente, Fin del programa\n" );
			break;
		}
		else {
			break;
		}
	}

	fclose(traza);
	fclose(archivo);


	exit(0);
}