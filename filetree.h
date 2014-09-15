
#ifndef FILETREE_H
#define FILETREE_H

#include <stdlib.h>
#include "list.h"
#define FALSE 0
#define TRUE  1

#define DIRECTORY 0
#define FILES      1

typedef struct Node_t
{
	char *name;
	char *path;
	int  type;
	int  nFile;
	List *listDir;
	List *listFile;
} Node;

Node *newNode(char* name, char *path, int type);

Node *findFile(List *list, char *name);

Node *changeDirectory(Node *root,char *path);

int split(char *source, char *path, char *name);

Node *newFile(Node *root, char *absName, int flag);

Node *removeFile(Node *root, char *absName);

void listDirectory(Node *root, char* path);

void showTree(Node *root);

#endif
