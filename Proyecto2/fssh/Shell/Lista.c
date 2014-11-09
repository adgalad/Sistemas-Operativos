//
//  Lista.c
//  Shell
//
//  Created by Carlos Spaggiari on 11/7/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#include "Lista.h"


NodePipe *addNode(ListNode *l, char *name){
    NodePipe *aux = (NodePipe*) malloc(sizeof(NodePipe));
    aux->next = NULL;
    aux->name = name;
    pipe(aux->fd);
    if (l == NULL) {
        l = (ListNode*) malloc(sizeof(ListNode));
    }
    if (l->head==NULL){
        l->head = aux;
        l->tail = aux;
    }
    else {
        l->tail->next = aux;
        l->tail       = aux;
    }
    return aux;
}

NodePipe *findNode(ListNode *l, char *name){
    NodePipe *aux = l->head;
    while (aux != NULL) {
        if (!strcmp(aux->name+1,name)){
            return aux;
        }
        aux = aux->next;
    }
    printf("fssh: %s: No such file or directory\n",name);
    return NULL;
}

void delNode(ListNode *l, char *name){
    NodePipe *aux1 = l->head, *aux2 = NULL;
    while (aux1 != NULL) {
        if (!strcmp(aux1->name+1,name)){
            if (aux2 != NULL){
                aux2->next = aux1->next;
            }
            free(aux1);
            return;
        }
        aux2 = aux1;
        aux1 = aux1->next;
    }
    printf("fssh: %s: No such file or directory\n",name);
}



