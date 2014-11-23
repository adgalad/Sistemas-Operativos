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
    FD *ph = NULL;
    FD *hp = NULL;
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
        auxi = hp->pd[0];
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
                ph_aux->sig = ph;
                ph = ph_aux;
                
                if ( (childpid = fork()) == 0 )  {
                    ruta = aux;
                    crearHijo(&father, ph, hp, &rs[0]);                   
                    goto directorio;
                    
                }
                else {
                    ph->id = childpid;
                    close(ph->pd[0]);
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
    
    
    if ( father == -1 ){
        padre(rs, ph, hp, argumentos, out, &father);
    }
    else {
        hijo(rs, ph, hp, auxi, argumentos, out, &father);
    }
    
    FD *aux_fd;
    aux_fd = ph;
    while( !(aux_fd == NULL) ){
        close(aux_fd->pd[1]);
        aux_fd = aux_fd->sig;
        free(ph);
        ph = aux_fd;
    }
    exit(0);
    
}