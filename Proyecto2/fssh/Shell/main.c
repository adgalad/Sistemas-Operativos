//
//  main.c
//  Shell
//
//  Created by Carlos Spaggiari on 11/3/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#include "Shell.h"

int main(int argc, const char * argv[]) {
    
    // Ignora la señal SIGINT para que no se detenga con el Cntrl+C.
    if (signal(SIGINT, SIG_IGN) == SIG_ERR){
        perror("Error couldn't ignore SIGINT");
        exit(EXIT_FAILURE);
    }
    
    
    // Mueve la direccion donde se ejecuta el proceso al directorio que se
    // da como argumento.
    if (argc > 1){
        if(chdir(argv[1]) == -1){
            perror("Error couldn't initialize shell");
        }
    }
    else{
        //perror("Error no arguments found");
        chdir("/hola");
        //exit(EXIT_FAILURE);
    }
    
    // Crea una lista con el nombre de cada directorio, el pipe y el pid
    // de su proceso correspondiente. El primer nodo que se crea es el nodo root
    ListNode *l = (ListNode*) malloc(sizeof(ListNode));
    addNode(l, "./");
    l->head->pid = getpid();
    
    // Se crea y se realiza un fork por cada nodo de dicha lista. dentro de la
    // funcion createTree(), los procesos hijos llaman la funcion waitCommand()
    // que esperara que el proceso root escriba sobre el pipe correspondiente.
    char *nameDir = malloc(1024);
    strcpy(nameDir,".");
    createTree(l, nameDir);
    
    
    int  nArg   = 0;
    char *cmd   =  malloc(256);
    char **args = (char**) malloc(sizeof(char*)*5);
    
    // Ciclo principal del proceso root. Contiene la interaccion con el usuario
    // y la comunicacion con los procesos hijos
    while (1) {

        // Imprime el prompt y lee un comando por stdin
        printf("fssh-1.0$ ");
        if(fgets(cmd, 255, stdin) == 0) {
            perror("Error when reading stdin");
            exit(EXIT_FAILURE);
        }
        
        // Secciona el string en comando y sus argumentos. Verifica si debe
        // escribir en un pipe hacia otro procesos o ejecutar el comando
        else{
            int len = (int)strlen(cmd);
            if (cmd[len-1] == '\n') cmd[len-1] = '\0';
            int dir = 0;
            for (int i = 0 ;  i < len; i++) {
                if (cmd[i] == ' ') {
                    cmd[i++] = '\0';
                    args[nArg++] = cmd+i;
                    if (nArg == 10) break;
                }
                if (cmd[i] == '/' && cmd[i+1] != ' '
                    && cmd[i+1] != '\0' && !dir)
                {
                    dir = nArg;
                }
            }
            
            // Se escribe el comando y sus argumentos en el pipe correspondiente
            if (dir != 0){
                int b = 0;
                NodePipe *node = findNode(l, args[dir-1]);
                if (node != NULL){
                    for(int i = 0 ; i < nArg ; i++){
                        *(args[i]-1) = ' ';
                    }
                    writePipe(node->fd, cmd);
                    char *buffer = readPipe(l->head->fd);
                    printf("%s",buffer);
                }
            }
            // Se ejecuta el comando
            else {
                if (!strcmp(cmd,"ls")){
                    ls(nArg,args,NULL);
                }
                else if (!strcmp(cmd,"cat")){
                    
                }
                else if (!strcmp(cmd,"cp")){
                    
                }
                else if (!strcmp(cmd,"mv")){
                    
                }
                else if (!strcmp(cmd,"find")){
                    
                }
                else if (!strcmp(cmd,"rm")){
                    
                }
                else if (!strcmp(cmd,"mkdir")){
                    
                }
                else if (!strcmp(cmd,"rmdir")){
                    
                }
                else if (!strcmp(cmd,"quit")){
                    NodePipe *node = l->head;
                    while (node != NULL) {
                        close(node->fd[0]);
                        write(node->fd[1],"quit", 4);
                        close(node->fd[1]);
                        node = node->next;
                    }
                    exit(EXIT_SUCCESS);
                }
                else if (argc <= 2 && !strcmp(cmd,"")){
                    printf("-fssh: %s: command not found\n",cmd);
                }
            }
            nArg = 0;
        }
    }
    return 0;
}









