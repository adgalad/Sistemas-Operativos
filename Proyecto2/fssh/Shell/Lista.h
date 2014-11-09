//
//  Lista.h
//  Shell
//
//  Created by Carlos Spaggiari on 11/6/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#ifndef Lista_h
#define Lista_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <signal.h>


typedef struct NodePipe_T{
    pid_t pid;
    int   fd[2];
    char* name;
    struct NodePipe_T *next;
}NodePipe;

typedef struct ListNode_T{
    struct NodePipe_T *head;
    struct NodePipe_T *tail;
}ListNode;



/* Funciones de la estructura Lista */
NodePipe *addNode(ListNode *l, char *name);

NodePipe *findNode(ListNode *l, char *name);

void delNode(ListNode *l, char *name);


#endif
