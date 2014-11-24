
#include "arbol.h"


FD **crearHijo (int *father, FD *fm[2], int *rs){
    if ( *father != -1 ) {
        *father = 0;
        close(fm[1]->pd[0]);   // Cierro la tuberia del abuelo
        free(fm[1]);           // Libero la estructura copiada del abuelo
        close(*rs);       // Cierro la tuberia de lectura para resultado
    }
                    
    *father = 0;
    fm[1] = fm[0];
    close(fm[1]->pd[1]);
    fm[0] = fm[0]->sig;
                    
    /**
    *********************************************************
        Limpieza de la estructura de hijos copiada del padre
    *********************************************************
    **/
    while( !(fm[0] == NULL) ){
        FD *aux_fd;
        aux_fd = fm[0];
        fm[0] = aux_fd->sig;
        free(aux_fd);
    }
    return fm;
}

void arbolActivo ( int father, FD *fm[2], int rs[2], char **argumentos, char *out, int auxi ) {
    if ( father == -1 ){
        padre(rs, fm, argumentos, out, &father);
    }
    else {
        hijo(rs, fm, auxi, argumentos, out, &father);
        close(rs[1]);
        FD *aux_fd;
        aux_fd = fm[0];
        while( !(aux_fd == NULL) ){
            close(aux_fd->pd[1]);
            aux_fd = aux_fd->sig;
            free(fm[0]);
            fm[0] = aux_fd;
        }
    }
    
    
}




void padre(int rs[2], FD *fm[2], char **argumentos, char *out, int* father) {
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
                aux_fd = fm[0];
                close(rs[0]);
                close(rs[1]);
                while ( aux_fd != NULL ) {
                    fm[0] = aux_fd->sig;
                    close(aux_fd->pd[1]);
                    free(aux_fd);
                    aux_fd = fm[0];
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
                comando(lecturals,argumentos, out,fm);
                write(rs[1],out, strlen(out)+1);
                goto resul;
            }


            
            aux_fd = fm[0];
            while ( strcmp(aux_fd->hijo, direccion) ){
                aux_fd1 = aux_fd;
                aux_fd = aux_fd->sig;
                if ( aux_fd == NULL ){
                    comando(lectura,argumentos, out,fm);
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
                            ph_aux->sig = fm[0];
                            fm[0] = ph_aux;
                            pid_t childpid;
                            if ( (childpid = fork()) == 0 )  {
                                crearHijo (father, fm, &rs[0]);
                                arbolActivo(*father, fm, rs, argumentos, out, fm[1]->pd[0]);                 
                            }
                            else {
                                fm[0]->id = childpid;
                                close(fm[0]->pd[0]);

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
                comando(lectura,argumentos, out,fm);
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


void hijo(int rs[2], FD *fm[2], int auxi , 
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
        FD *aux_fd1;
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
        while ( strcmp(direccion, fm[1]->hijo) ) {
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
            comando(instruccion,argumentos, out,fm);
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
                    if (fm[0] == NULL) {
                        comando(instruccion,argumentos, out,fm);
                        write(rs[1],out, strlen(out)+1);
                    }
                    else {
                        aux_fd = fm[0];
                        while (1){
                            
                            if ( aux_fd == NULL ) {
                                comando(instruccion,argumentos, out,fm);
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
                        comando(instruccion,argumentos, out,fm);
                    if ( strcmp(out, "0") ) {
                        //No se creo el directorio
                    }
                    else {
                        sprintf(out,"");
                        FD *ph_aux = (FD *)malloc(sizeof(FD));
                        pipe(ph_aux->pd);
                        ph_aux->hijo = malloc(30);
                        strcpy(ph_aux->hijo,direccion);
                        ph_aux->sig = fm[0];
                        fm[0] = ph_aux;
                        pid_t childpid;
                        if ( (childpid = fork()) == 0 )  {
                            crearHijo (father, fm, &rs[0]);
                            arbolActivo(*father, fm, rs, argumentos, out, fm[1]->pd[0]);                 
                        }
                        else {
                            fm[0]->id = childpid;
                            close(fm[0]->pd[0]);
                        }

                    }
                    write(rs[1],out, strlen(out)+1);

                }
                else if ( !strcmp(comandop,"rmdir") ) {
                    comando(instruccion,argumentos, out,fm);
                    if ( strcmp(out, "0") ){
                        //No se elimino el directorio
                    }
                    else {
                        sprintf(out,"");
                        // Manda señal de SIGKILL al hijo
                        aux_fd = fm[0];
                        while ( !strcmp(aux_fd->hijo, direccion) ){
                            aux_fd1 = aux_fd;
                            aux_fd = aux_fd->sig;
                        }
                        kill(aux_fd->id, 9);
                        aux_fd1->sig = aux_fd->sig;
                        free(aux_fd);

                    }
                }
                else {
                    comando(instruccion,argumentos, out,fm);
                    write(rs[1],out, strlen(out)+1);
                }
            }
            else {
                aux_fd = fm[0];
                while ( 1 ) {
                    if (!strcmp(aux_fd->hijo, direccion)) {
                        write(aux_fd->pd[1], instruccion, strlen(instruccion)+1);
                        break;
                    }
                    else if ( aux_fd == NULL ) {
                        comando(instruccion,argumentos, out,fm);
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