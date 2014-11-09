//
//  Shell.h
//  Shell
//
//  Created by Carlos Spaggiari on 11/8/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#ifndef Shell_h_
#define Shell_h_

#include "Lista.h"

/**********************/
/* Comandos del shell */
/**********************/

void ls(int argc,char **argv,NodePipe *root);

void cat(int argc, char **argv, NodePipe *root);

/**********************************/
/* Funciones esenciales del shell */
/**********************************/

// Se encarga de esperar y ejecutar los comandos que son escritos
// por el proceso root en el pipe del proceso correspondiente
void waitCommand(NodePipe *node, NodePipe *root);

// Crea una lista de nodos que representan a cada directorio que
// abarca el shell. Cada nodo posee el file descriptor del pipe y
// el nombre del directorio (path absoluto).
void createTree(ListNode *l,char *nameDir);

// Funcion que dado un file descriptor y un string, escribe en el pipe
ssize_t writePipe(int fd[2], char *buffer);

// Funcion que lee de un pipe dado por el file descriptor
char *readPipe(int fd[2]);

#endif /* defined(__Shell__Shell__) */
