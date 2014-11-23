
#include "arbol.h"







void padre(int rs[2], FD *ph, char **argumentos, char *out)
{
    char lectura[100];
    char tokken[100];
    char resultado[1000];
    char *direccion;
    char *comandop;
    while(1)
    {
        printf("fssh$ ");
        fgets(lectura,100, stdin);
        if ( !strcmp(lectura, "\n") ) {
            printf("\n");
        }
        else {
            FD *aux_fd;
            
            if ( lectura[strlen(lectura)-1] == '\n' ){
                lectura[strlen(lectura)-1] = '\0';
            }
            
            strcpy(tokken, lectura);
            direccion = strtok(tokken, " ");
            comandop = malloc(sizeof(direccion)+1);
            strcpy(comandop, direccion);
            direccion = strtok(NULL," ");
            direccion = strtok(direccion, "/");
            
            /**
             ***************************************************************
             Cierre de todos los Pipes y terminacion del proceso raiz
             ***************************************************************
             **/
            
            if ( !strcmp(comandop, "quit") ){
                aux_fd = ph;
                while ( aux_fd != NULL ) {
                    ph = aux_fd->sig;
                    close(aux_fd->pd[1]);
                    free(aux_fd);
                    aux_fd = ph;
                }
                free(comandop);
                exit(0);
            }
            
            if ( !strcmp(comandop, "find") ){
                //Ejecute codigo de find
                free(comandop);
            }
            
            
            if ( direccion == NULL || !strcmp(direccion,"/")) {
                // Ejecutar Instruccion
                comando(lectura,argumentos, out);
                write(rs[1],out, strlen(out)+1);
                goto resul;
            }
            
            aux_fd = ph;
            while ( strcmp(aux_fd->hijo, direccion) ){
                aux_fd = aux_fd->sig;
                if ( aux_fd == NULL ){
                    comando(lectura,argumentos, out);
                    write(rs[1],out, strlen(out)+1);
                    free(comandop);
                    goto resul;
                }
            }
            write(aux_fd->pd[1], lectura, strlen(lectura)+1);
        resul:	read(rs[0], resultado,1000);
            printf("%s", resultado);
        }
    }
}


void hijo(int rs[2], FD *ph, FD *hp, int auxi , char ** argumentos, char *out)
{
    /**
     *****************************************
     Comunicacion entre procesos
     *****************************************
     **/
    
    int status;
    status = 420;
    char instruccion[100];
    
    
    while ( status != 0 ){
        int aux1, aux2;
        FD *aux_fd;
        status = read(auxi, instruccion,100);
        char *tokken;
        char *direccion;
        char *direccion1;
        char *comandop;
        tokken = malloc(sizeof(instruccion)+1);
        
        
        strcpy(tokken, instruccion);
        direccion = strtok(tokken, " ");
        comandop = malloc(sizeof(direccion)+1);
        strcpy(comandop, direccion);
        
        direccion = strtok(NULL," ");
        
        direccion = strtok(direccion, "/");
        
        aux1 = 0;
        while ( strcmp(direccion, hp->hijo) ) {
            direccion = strtok(NULL, "/");
            aux1++;
        }
        direccion = strtok(NULL, "/");
        aux1++;
        
        strcpy(tokken, instruccion);
        direccion1 = strtok(tokken, " ");
        direccion1 = strtok(NULL," ");
        direccion1 = strtok(direccion1, "/");
        
        aux2 = 0;
        while ( direccion1 != NULL ) {
            direccion1 = strtok(NULL, "/");
            aux2++;
        }
        
        if ( aux1 == aux2 ) {
            // Ejecutar Instruccion
            comando(instruccion,argumentos, out);
            write(rs[1],out, strlen(out)+1);
        }
        else {
            /**
             *******************************************************************
             Verificacion si el ultimo nombre de la ruta es un directorio
             o un archivo
             *******************************************************************
             **/
            
            if ( aux2 - aux1 >= 1 ) {
                if ( !strcmp(comandop, "ls") ) {
                    if (ph == NULL) {
                        comando(instruccion,argumentos, out);
                        write(rs[1],out, strlen(out)+1);
                    }
                    else {
                        aux_fd = ph;
                        while (1){
                            
                            if ( aux_fd == NULL ) {
                                comando(instruccion,argumentos, out);
                                write(rs[1],out, strlen(out)+1);
                                break;
                            }
                            else if (!strcmp(aux_fd->hijo, direccion)) {
                                write(aux_fd->pd[1], instruccion,
                                      strlen(instruccion)+1);
                                break;
                            }
                            aux_fd = aux_fd->sig;
                        }
                    }
                }
                else {
                    comando(instruccion,argumentos, out);
                    write(rs[1],out, strlen(out)+1);
                }
                free(comandop);
            }
        }
        free(tokken);
    }
}


/**
 *****************************************
 Manejador de señales para los hijos.
 *****************************************
 **/

void childHandler () {
    int childPid, childStatus;
    childPid = wait(&childStatus);
    printf("El hijo %d termino\n",childPid);
}