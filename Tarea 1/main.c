/* Estructura principal de la tarea1
 * Autores:
 */

 /* Comandos principales: md: Crear directorio, ma: Crear Archivo, 
  *	rm: Eliminar archivo o directorio vacio, ls: Listar archivos del directorio
  */



#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "archivo.h"

int main ( int argc, char **argv ) {
	*argv++;
	FILE *archivoin = fopen( *argv, "r");

	if ( archivoin == NULL ) {
		printf("\n Error en la lectura del archivo \n");
		exit(1);
	}

	char *comando = (char *)malloc(sizeof(char)*2);
	FILE *traza = fopen( "traza.txt", "w");
	archivo *raiz = (archivo *)malloc(sizeof(archivo));
	raiz->nombre = "/";
	raiz->tipo = true;
	raiz->numarchi = 0;
	raiz->sig = NULL;
	raiz->hijo = NULL;

	while ( fscanf(archivoin, "%s\t", comando ) ) {
		if ( strcmp(comando, "ma") == 0 ) {
			char *argumento = (char *)malloc(sizeof(char)*100);
			char *s = "/";
			char *tokken;
			fscanf(archivoin, "%s\n", argumento);
			tokken = strtok(argumento, s);
			archivo *directorio;
			directorio = raiz;
			Crear_archivo(&directorio, &tokken);

			}
		else if ( strcmp(comando, "md") == 0 ) {
			char *argumento = (char *)malloc(sizeof(char)*100);
			char *s = "/";
			char *tokken;
			fscanf(archivoin, "%s\n", argumento);
			tokken = strtok(argumento, s);
			archivo *directorio;
			directorio = raiz;
			Crear_directorio(&directorio, &tokken);

			}
		else if( strcmp(comando, "ls") == 0 ) {
			char *argumento = (char *)malloc(sizeof(char)*100);
			char *s = "/";
			char *tokken;
			fscanf(archivoin, "%s\n", argumento);
			tokken = strtok(argumento, s);
			archivo *directorio;
			directorio = raiz;
			Listar_archivos(&directorio, &tokken);

		}
		else if( strcmp(comando, "rm") == 0 ) {
			char *argumento = (char *)malloc(sizeof(char)*100);
			char *s = "/";
			char *tokken;
			fscanf(archivoin, "%s\n", argumento);
			tokken = strtok(argumento, s);
			archivo *directorio;
			directorio = raiz;
			Eliminar_archivos(&directorio, &tokken);

		}
		else {
			printf("Recorrido Breadth first search al directorio:\n\n");
			Bfs(&raiz);
			break;
		}
	}
}