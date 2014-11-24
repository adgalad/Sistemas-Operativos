
#include "arbol.h"


void crearHijo (int *father, FD *ph, FD *hp, int *rs){
    if ( *father != -1 ) {
        *father = 0;
        close(hp->pd[0]);   // Cierro la tuberia del abuelo
        free(hp);           // Libero la estructura copiada del abuelo
        close(*rs);       // Cierro la tuberia de lectura para resultado
    }
                    
    *father = 0;
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

}

void arbolActivo ( int father, FD *ph, FD *hp, int rs[2], char **argumentos, char *out, int auxi ) {
    if ( father == -1 ){
        padre(rs, ph, hp, argumentos, out, &father);
    }
    else {
        hijo(rs, ph, hp, auxi, argumentos, out, &father);
        close(rs[1]);
        FD *aux_fd;
        aux_fd = ph;
        while( !(aux_fd == NULL) ){
            close(aux_fd->pd[1]);
            aux_fd = aux_fd->sig;
            free(ph);
            ph = aux_fd;
        }
    }
    
    
}




void padre(int rs[2], FD *ph, FD *hp, char **argumentos, char *out, int* father) {
    char lectura[100];
    char tokken[100];
    char resultado[1000];
    char *direccion;
    char *comandop;
    char *direccion1;
    while(1)  {
        printf("fssh$ ");
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
                close(rs[0]);
                close(rs[1]);
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
            }


            
            
            if ( ( direccion == NULL || !strcmp(direccion,"/") ) 
                & !strcmp(comandop,"ls") ){
                // Ejecutar Instruccion
                char lecturals[5] = "ls /\n";
                comando(lecturals,argumentos, out);
                write(rs[1],out, strlen(out)+1);
                goto resul;
            }


            
            aux_fd = ph;
            while ( strcmp(aux_fd->hijo, direccion) ){
                aux_fd1 = aux_fd;
                aux_fd = aux_fd->sig;
                if ( aux_fd == NULL ){
                    comando(lectura,argumentos, out);
                    if ( !strcmp(comandop, "mkdir") ) {
                        if ( strcmp(out, "0") ) {
                            //No se creo el directorio
                            goto resul;
                        }
                        else {
                            sprintf(out,"");
                            FD *ph_aux = (FD *)malloc(sizeof(FD));
                            pipe(ph_aux->pd);
                            ph_aux->hijo = malloc(30);
                            strcpy(ph_aux->hijo,direccion);
                            ph_aux->sig = ph;
                            ph = ph_aux;
                            pid_t childpid;
                            if ( (childpid = fork()) == 0 )  {
                                if ( *father != -1 ) {
                                    *father = 0;
                                    close(hp->pd[0]);   // Cierro la tuberia del abuelo
                                    free(hp);           // Libero la estructura copiada del abuelo
                                    close(*rs);       // Cierro la tuberia de lectura para resultado
                                }
                            
                                *father = 0;
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
                                arbolActivo(*father, ph, hp, rs, argumentos, out, hp->pd[0]);                 
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
            
            direccion1 = strtok(direccion, "/");
            direccion1 = strtok(NULL, "/");
            if ( !strcmp(comandop, "rmdir") & (direccion1 == NULL) ){
                comando(lectura,argumentos, out);
                if ( strcmp(out, "0") ){
                    //No se elimino el directorio
                    goto resul;

                }
                else {
                    sprintf(out,"");
                    // Manda señal de SIGKILL al hijo
                    kill(aux_fd->id, 9);
                    aux_fd1->sig = aux_fd->sig;
                    free(aux_fd);
                    write(rs[1],out, strlen(out)+1);
                    goto resul;

                }
            }
            write(aux_fd->pd[1], lectura, strlen(lectura)+1);
resul:	    free(comandop);
            read(rs[0], resultado,1000);
            printf("%s", resultado);
        }
    }
}


void hijo(int rs[2], FD *ph, FD *hp, int auxi , 
            char ** argumentos, char *out, int *father) {
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
            
            if ( aux2 - aux1 == 1 ) {
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
                else if ( !strcmp(comandop, "mkdir") ) {
                        comando(instruccion,argumentos, out);
                    if ( strcmp(out, "0") ) {
                        //No se creo el directorio
                    }
                    else {
                        sprintf(out,"");
                        FD *ph_aux = (FD *)malloc(sizeof(FD));
                        pipe(ph_aux->pd);
                        ph_aux->hijo = malloc(30);
                        strcpy(ph_aux->hijo,direccion);
                        ph_aux->sig = ph;
                        ph = ph_aux;
                        pid_t childpid;
                        if ( (childpid = fork()) == 0 )  {
                            if ( *father != -1 ) {
                                    *father = 0;
                                    close(hp->pd[0]);   // Cierro la tuberia del abuelo
                                    free(hp);           // Libero la estructura copiada del abuelo
                                    close(*rs);       // Cierro la tuberia de lectura para resultado
                                }
                            
                            *father = 0;
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
                            arbolActivo(*father, ph, hp, rs, argumentos, out, hp->pd[0]);                 
                        }
                        else {
                            ph->id = childpid;
                            close(ph->pd[0]);
                        }

                    }
                    write(rs[1],out, strlen(out)+1);

                }
                else {
                    comando(instruccion,argumentos, out);
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
                        comando(instruccion,argumentos, out);
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
            Manejador de señales 
 *****************************************
 **/



void Handler () { 
    return;

}