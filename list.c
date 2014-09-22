

#include "list.h"

List *listConstructor()
{
	List *list = (List*) malloc(sizeof(List));
	list->node = NULL;
	list->next = NULL;
	return list;
}

List *add(List *list, struct Node_t *node)
{
	List *newNode = listConstructor();
	newNode->node = node;
	newNode->next = list;
	list          = newNode;

	return list;
}

Queue *queueConstructor()
{
	Queue *q = (Queue*)malloc(sizeof(Queue));
	q->head = NULL;
	q->tail = NULL;
	return q;
}
void *addQueue(Queue *q, struct Node_t *node)
{
	List *newNode = listConstructor();
	newNode->node = node;
	newNode->next = NULL;
	if(q->head == NULL)
	{
		q->head = newNode;
		q->tail = newNode;
	}
	else
	{
		q->tail->next = newNode;
		q->tail = newNode;
	}
}

struct Node_t *removeQueue(Queue *q)
{
	if (q->head == NULL) return NULL;
	struct Node_t *node = q->head->node;
	q->head = q->head->next;
	return node;
}
