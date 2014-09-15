

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct Node_t;

typedef struct List_t
{
	struct Node_t *node;
	struct List_t *next;	
}List;

List *listConstructor();

List *add(List *list, struct Node_t *node);

typedef struct Queue_t
{
	List *head;
	List *tail;
}Queue;

Queue *queueConstructor();

void *addQueue(Queue *q, struct Node_t *node);

struct Node_t *removeQueue(Queue *q);

#endif
