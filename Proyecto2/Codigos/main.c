//
//  main.c
//  fssh
//
//  Created by Carlos Spaggiari on 11/23/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#include "arbol.h"


int main (int argc, char** argv) {
    
    signal(SIGINT, Handler);
    signal(SIGQUIT, Handler);
    struct stat inodo;
    int father = -1;
    DIR *dirp;
    struct dirent *direntp;
    char *ruta = argv[1];
    pid_t childpid;
    FD *fm[2];
    int rs[2];
    int auxi = 0;
    char **argumentos = (char **) malloc (sizeof(char*)*6);
    char *out = malloc(1024);
    chdir(argv[1]);

    if (stat(ruta, &inodo) == -1 ) {
        fprintf(stderr, "No se pudo aplicar stat sobre el archivo %s: %s \n"
                ,ruta, strerror(errno));
        exit(1);
    }
    if ( !(inodo.st_mode & S_IFDIR) ) {
        fprintf(stderr, "La ruta especificada no es un Directorio\n");
        exit(1);
    }
    
    pipe(rs);
    
directorio:
    
    /**
     *************
         Cable
     *************
     **/
    
    if ( father == 0 ) {
        auxi = fm[1]->pd[0];
    }
    
    
    /**
     ******************************************************
        Imprimimos la Ruta actual y la modificamos para
         que pueda ser interpretada como ruta absoluta
     ******************************************************
     **/
    
    if ( ! (ruta[strlen(ruta)-1] == '/') ){
        strcat(ruta,"/");
    }
    
    if ( ! strcmp(ruta, "../") ) {
        strcpy(ruta,"./");
        if ( (dirp = opendir(ruta) ) == NULL ){
            fprintf(stderr, "No se pudo abrir el directorio\n");
            exit(1);
        }
    }
    else {
       if ( (dirp = opendir(ruta)) == NULL ) {
            fprintf(stderr, "No se pudo abrir el directorio\n");
            exit(1);
        }
    }
    
    
    /**
     ****************************************************
         Buscamos en la tabla de inodos del directorio
     ****************************************************
     **/
skip:
    while (( direntp = readdir(dirp)) != NULL ) {
        if ('.' == direntp->d_name[0]) {
            goto skip;
        }
        /**
         ***********************************************************
             Construccion de la ruta absoluta del subdirectorio
         ***********************************************************
         **/
        
        char *aux = (char *)malloc(strlen(ruta) + strlen(direntp->d_name) + 1);
        strcpy(aux,ruta);
        strcat(aux,direntp->d_name);
        
        
        if (stat(aux, &inodo) == -1 ) {
            fprintf(stderr, "No se pudo aplicar stat sobre el archivo %s: %s \n"
                    ,aux, strerror(errno));
            exit(1);
        }
        else {
            if ( inodo.st_mode & S_IFDIR ) {
                /**
                 ***********************************************************
                     Estructura auxiliar para comunicacion con los hijos
                 ***********************************************************
                 **/
                
                FD *ph_aux = (FD *)malloc(sizeof(FD));
                pipe(ph_aux->pd);
                ph_aux->hijo = malloc(30);
                strcpy(ph_aux->hijo, direntp->d_name);
                ph_aux->sig = fm[0];
                fm[0] = ph_aux;
                if ( (childpid = fork()) == 0 )  {
                    ruta = aux;
                    crearHijo (&father, fm, &rs[0]);
                    goto directorio;
                    
                }
                else {
                    fm[0]->id = childpid;
                    close(fm[0]->pd[0]);
                }
            }
        }
        free(aux);
    }
    closedir(dirp);
    
    
    
    /**
     *****************************************
                Entrada de Comandos
     *****************************************
     **/
    
    arbolActivo(father, fm, rs, argumentos, out, auxi);

    exit(0);

 
}
