//
//  Shell.c
//  Shell
//
//  Created by Carlos Spaggiari on 11/8/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#include "Shell.h"


void ls(int argc,char **argv,NodePipe *root){
    DIR  *directory;
    char *nameDir = malloc(256);
    char *buffer = malloc(1024);
    strcpy(nameDir,".");
    strcat(nameDir,argv[0]);
    directory = opendir(nameDir);
    if (!directory){
        strcpy( buffer , "fssh: ");
        strcat( buffer , nameDir+1);
        strcat( buffer , ": No such file or directory\n");
    }
    else while (1) {
        struct dirent *files;
        files = readdir (directory);
        if (! files) {
            closedir(directory);
            break;
        }
        strcat(buffer,files->d_name);
        strcat(buffer,"\n");
    }
    if (root != NULL){
        writePipe(root->fd, buffer);
    }
    else {
        printf("%s",buffer);
    }
}

void cat(int argc, char **argv, NodePipe *root){
    DIR *directory;
    char *nameDir = malloc(255);
    strcpy(nameDir,".");

    directory = opendir(nameDir);
    while (1) {
        break;
    }
}


void waitCommand(NodePipe *node, NodePipe *root){
    while (1) {
        // Lee el pipe y separa el string leido en comando y argumentos
        char *cmd = readPipe(node->fd);
        int i = 0;
        char *argv[10];
        int  argc = 0;        
        for (int i = 0 ;  i < strlen(cmd); i++) {
            if (cmd[i] == ' ') {
                cmd[i++] = '\0';
                argv[argc++] = cmd+i;
            }
        }
        
        // Ejecuta el comando
        if (!strcmp(cmd,"ls")){
            ls(argc,argv,root);
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
            exit(EXIT_SUCCESS);
        }
        else{
            char *buffer = malloc(40);
            strcpy(buffer, "-fssh: ");
            strcat(buffer, cmd);
            strcat(buffer, ": command not found\n");
            writePipe(root->fd, buffer);
        }
    }
}

void createTree(ListNode *l,char *nameDir){
    DIR *directory = opendir(nameDir);
    if (directory == NULL){
        perror(nameDir);
        exit(EXIT_FAILURE);
    }
    pid_t pid;
    
    struct dirent *file = readdir (directory);
    while (file) {
        if (file->d_type == 4 && file->d_name[0] != '.')
        {
            NodePipe *aux;
            char *strAux = malloc(strlen(nameDir)+strlen(file->d_name));
            strcpy(strAux,nameDir);
            strcat(strAux, "/");
            strcat(strAux,file->d_name);
            aux = addNode(l,strAux);
            if((pid = fork()) == -1){
                perror("Error: fork");
                exit(EXIT_FAILURE);
            }
            else if (pid == 0){
                waitCommand(aux,l->head);
                return;
            }
            else{
                aux->pid = pid;
                createTree(l, aux->name);
            }
        }
        file = readdir(directory);
    }
}


ssize_t writePipe(int fd[2], char *buffer){
    close(fd[0]);
    ssize_t n = write(fd[1], buffer, strlen(buffer));
    return n;
}

char *readPipe(int fd[2]){
    char *buffer = malloc(1024);
    close(fd[1]);
    while(read(fd[0], buffer, 1024) < 0);
    return buffer;
}


