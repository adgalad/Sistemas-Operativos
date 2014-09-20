/* Tarea 1 
 * TAD archivo
 * Autor: 
 */

#include "archivo.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 void Llegar_ruta( archivo **raiz, char **tokken ){
 	char *aux;
 	archivo *directorio;
 	directorio = *raiz;
 	aux = *tokken;
 	*tokken = strtok(NULL,"/");

 	while ( *tokken != NULL ){
 		directorio = directorio->hijo;
 		if ( directorio == NULL ){
 			printf("\n La ruta no existe1 \n");
        	exit(1);
 		}
 		while ( strcmp( aux, directorio->nombre ) != 0 ) {
 			directorio = directorio->sig;
 			if ( directorio == NULL ){
 				printf("\n La ruta no existe \n");
        		exit(1);
 			}
 		}
 		aux = *tokken;
 		*tokken = strtok(NULL, "/");

 	}
 	*tokken = aux;
 	*raiz = directorio;
 }

 void Crear_archivo( archivo **raiz, char **tokken ){
 	archivo *directorio;
 	directorio = *raiz;
 	Llegar_ruta( &directorio, &*tokken);
 	archivo *aux = (archivo*)malloc(sizeof(archivo));
 	aux->nombre = *tokken;
 	aux->tipo = false;
 	aux->numarchi = 0;
 	aux->sig = NULL;
 	aux->hijo = NULL;
 	directorio->numarchi++;
 	if ( directorio->hijo != NULL ) {
 		directorio = directorio->hijo;
 		while ( directorio->sig != NULL ) {
 			directorio = directorio->sig;
 		}
 		directorio->sig = aux;

 		printf("Se ha creado %s\n", directorio->sig->nombre);
 	}
 	else {
 		directorio->hijo = aux;
 		printf("Se ha creado %s\n", directorio->hijo->nombre);
 	}
 	 	
 }


 void Crear_directorio( archivo **raiz, char **tokken){
 	archivo *directorio;
 	directorio = *raiz;
 	Llegar_ruta(&directorio, &*tokken);
 	archivo *aux = (archivo*)malloc(sizeof(archivo));
 	aux->nombre = *tokken;
 	aux->tipo = true;
 	aux->numarchi = 0;
 	aux->sig = NULL;
 	aux->hijo = NULL;
 	directorio->numarchi++;
 	if ( directorio->hijo != NULL ) {
 		directorio = directorio->hijo;
 		while ( directorio->sig != NULL ) {
 			directorio = directorio->sig;
 		}
 		directorio->sig = aux;

 		printf("Se ha creado %s\n", directorio->sig->nombre);
 	}
 	else {
 		directorio->hijo = aux;
 		printf("Se ha creado %s\n", directorio->hijo->nombre);
 	}


 }


 void Listar_archivos ( archivo **raiz, char **tokken) {
 	archivo *directorio;
 	directorio = *raiz;
 	if ( *tokken != NULL){
 		Llegar_ruta(&directorio, &*tokken);
 		if ( directorio->hijo == NULL ) {
 			printf("La ruta no existe\n");
 			exit(1);
 		}
 		directorio = directorio->hijo;
 		while ( strcmp( directorio->nombre, *tokken ) != 0 ) {
 			directorio = directorio->sig;
 			if ( directorio == NULL ){
 				printf("\n La ruta no existe \n");
        		exit(1);
 			}
 		}
 		if ( directorio->hijo == NULL ) {
 			printf("El directorio esta vacio\n");
 		}
 		else {
 			directorio = directorio->hijo;
 			while ( directorio != NULL ){
 				printf("%s tipo de archivo: %s\n", directorio->nombre, Tipo_archivo(directorio->tipo));
 				directorio = directorio->sig;

 			}
 		}
 	}
 	else {
 		directorio = directorio->hijo;
 		while ( directorio != NULL ){
 			printf("%s tipo de archivo: %s\n", directorio->nombre, Tipo_archivo(directorio->tipo));
 			directorio = directorio->sig;
 		}
 	}

 }


 char* Tipo_archivo( bool tipo ){
 	if ( tipo == true ) {
 		char *tipod = "Directorio";
 		return tipod;
 	}
 	else {
 		char *tipod = "Archivo";
 		return tipod;
 	}
 }