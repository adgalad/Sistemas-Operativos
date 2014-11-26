
#include "arbol.h"






void padre(int rs[2], FD *ph, FD *hp, int auxi, char **argumentos, char *out, int father)
{
    char lectura[100];
    char tokken[100];
    char resultado[10000];
    char *direccion;
    char *direccion1;
    char *comandop;
    while(1)
    {
prompt: printf("fssh$ ");
        fgets(lectura,100, stdin);
        if ( !strcmp(lectura, "\n") ) {
            printf("\n");
        }
        else {
            FD *aux_fd;
            FD *aux_fd1;
            
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
                /*
                while ( aux_fd != NULL ) {
                    ph = aux_fd->sig;
                    close(aux_fd->pd[1]);
                    free(aux_fd);
                    aux_fd = ph;
                }*/
                exit(0);
            }
            
            if ( !strcmp(comandop, "find") ){
                comando(lectura,argumentos,out, rs,ph,hp);
								goto resul;
            }
            
            
            if ( direccion == NULL || !strcmp(direccion,"/")) {
                // Ejecutar Instruccion
                comando(lectura,argumentos, out, rs,ph,hp);
                write(rs[1],out, strlen(out)+1);
                goto resul;
            }
            
            aux_fd = ph;
            while ( strcmp(aux_fd->hijo, direccion) ){
                aux_fd = aux_fd->sig;
                if ( aux_fd == NULL ){
                    comando(lectura,argumentos, out, rs,ph,hp);
                    if (!strcmp(comandop, "mkdir")){
                        if (!strcmp(out, "")){
                            
                            FD *ph_aux = (FD*)malloc(sizeof(FD));
                            pipe(ph_aux->pd);
                            ph_aux->hijo = malloc(30);
                            strcpy(ph_aux->hijo, direccion);
                            ph_aux->sig = ph;
                            ph = ph_aux;
                            int childpid;
                            if((childpid = fork()) == 0) {
                                char *concat = malloc(strlen(ph->hijo)+strlen(hp->path)+3);
                                strcpy(concat, hp->path);
                                strcat(concat, ph->hijo);
                                strcat(concat, "/");
                                
                                father = 0;
                                hp = ph;
                                close(hp->pd[1]);
                                ph = ph->sig;
                               	
                                /**
                                 *********************************************************
                                 Limpieza de la estructura de hijos copiada del padre
                                 *********************************************************
                                 **/
                                while( !(ph == NULL) ){
                                    FD *aux_fd;
                                    aux_fd = ph;
                                    ph = aux_fd->sig;
                                    free(aux_fd);
                                }
                                hp->path = concat;
                                hijo(rs, ph, hp, hp->pd[0], argumentos, resultado, father);
                            }
                            else {
                                ph->id = childpid;
                                close(ph->pd[0]);
                            }
                        }
                    }

                    write(rs[1],out, strlen(out)+1);
                    goto resul;
                }
            }

            direccion1 = strtok(direccion, "/"),
            direccion1 = strtok(NULL, "/");
            if (!strcmp(comandop, "rmdir") & (direccion1 == NULL) ) {
                comando(lectura,argumentos, out,rs, ph, hp);
                if ( !strcmp(out,"") ){
                    aux_fd = ph;
                    while ( strcmp(aux_fd->hijo, direccion) ){
                        aux_fd1 = aux_fd;
                        aux_fd = aux_fd->sig;
                    }
                    kill(aux_fd->id,9);
                    if ( aux_fd1 == NULL ){
                        aux_fd1 = aux_fd;
                        ph = aux_fd->sig;
                        free(aux_fd1);
                    }
                    else {
                        aux_fd1->sig = aux_fd->sig;
                        free(aux_fd);
                        
                    }
                    write(rs[1],out, strlen(out)+1);
                    goto resul;
                }
            }
            write(aux_fd->pd[1], lectura, strlen(lectura)+1);
    resul:	read(rs[0], resultado,10000);
            free(comandop);
            printf("%s", resultado);
        }
    }
}


void hijo(int rs[2], FD *ph, FD *hp, int auxi , char ** argumentos, char *out, int father)
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
            comando(instruccion,argumentos, out, rs,ph,hp);
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
                        comando(instruccion,argumentos, out, rs,ph,hp);
                        write(rs[1],out, strlen(out)+1);
                    }
                    else {
                        aux_fd = ph;
                        while (1){
                            
                            if ( aux_fd == NULL ) {
                                comando(instruccion,argumentos, out, rs,ph,hp);
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
                    comando(instruccion,argumentos, out, rs,ph,hp);
                    write(rs[1],out, strlen(out)+1);
                }
            }
            else {
                aux_fd = ph;
                while ( 1 ) {
                    if (!strcmp(aux_fd->hijo, direccion)) {
                        write(aux_fd->pd[1], instruccion, strlen(instruccion)+1);
                        break;
                    }
                    else if ( aux_fd == NULL ) {
                        comando(instruccion,argumentos, out, rs,ph,hp);
                        write(rs[1],out, strlen(out)+1);
                        break;
                    }
                    aux_fd = aux_fd->sig;
                }
            }
            free(comandop);
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
