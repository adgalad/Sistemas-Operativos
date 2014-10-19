
#include "filetree.h"

Node *newNode(char* name, char *path, int type, Node *parent)
{
	Node *node = (Node*) malloc(sizeof(Node));
	node->name = malloc(255);
	node->path = malloc(255);
	strcpy(node->name, name);
	strcpy(node->path, path);
	node->type     = type;
	node->nFile    = 0;
	node->listDir  = NULL;
	node->listFile = NULL;
	parent 		   = parent;

	return node;
}

Node *findFile(List *list, char *name)
{
	List *iterator = list;
	while(iterator!=NULL)
	{
		if ( strcmp(iterator->node->name, name) == 0 )
			return iterator->node;
		iterator = iterator->next;
	}
	return NULL;
}

Node *changeDirectory(Node *root,char *path)
{
	int i=1, j=1, length = strlen(path);
	Node *node = root;
	if (!strcmp(path,".."))
	{
		if (root->parent != NULL)
			return root->parent;
		else
			return root;
	}
	if(path[0] != '/')
	{
		printf("ERROR: No such file or directory.\n");
		return NULL;
	}
	if (strlen(path) == 1) return root;
	while(TRUE)
	{
		while(path[j] != '\0' && path[j] != '/')
			j++;

		path[j] = '\0'; 
		node = findFile(node->listDir, path+i);
		
		if (node == NULL)
		{
			printf("ERROR: No such file or directory.\n");
			return NULL;
		}
		else if (j == length) return node;
		path[j] = '/';
		i = ++j;
	}
}

int split(char *source, char *path, char *name)
{
	int i = strlen(source)-1;
	if(source[0] != '/') return FALSE;
	
	while (source[i] != '/')
		i--;

	if (i==0)	strncpy(path, source, i+1);
	else     	strncpy(path, source, i);
	strncpy(name, source + (i+1), strlen(source)-i);
	
	return TRUE;
}

Node *newFile(Node *root, char *absName, int flag)
{
	char *path = malloc(255),
	     *name = malloc(255);
	Node *node;
	if (!split(absName, path, name))
	{
		printf("ERROR: No such file or directory.\n");
		return root;
	}
	else if(strlen(name) == 0)
	{
		printf("ERROR: Couldn't create such file or directory.\n");
		return root;
	}
	
	node = changeDirectory(root,path);
	if (node == NULL) return root;
	if(flag)
	{
		if(findFile(node->listFile, name) != NULL)
				printf("ERROR: File or directory already exists.\n");
		else
		{
			node->listFile = add(node->listFile, newNode(name, path, flag,node));
			node->nFile++;
			
		}
	}
	else
	{
		if(findFile(node->listDir, name) != NULL)
				printf("ERROR: File or directory already exists.\n");
		else
		{
			node->listDir = add(node->listDir, newNode(name, path, flag, node));
			node->nFile++;
		}
	}
	return root;
}

Node *removeFile(Node *root, char *absName)
{
	char *path = malloc(255),
		 *name = malloc(255);
	Node *node;
	List *list, 
		 *lastNode;	

	split(absName, path, name);
	node = changeDirectory(root,path);
	if (node == NULL) return root;

	int type;
	list = node->listDir;
	for(type = 0 ; type <2 ; type++)
	{
		int i = 1;
		lastNode=NULL;
		while(list!=NULL)
		{
			if(strcmp(list->node->name, name) == 0) 
			{
				if (type || !list->node->nFile)
				{
					if (lastNode == NULL)
						if (type)
						{ 
							node->listFile = node->listFile->next;
						}
						else
						{
						    node->listDir  = node->listDir->next;
						}
					else
						lastNode->next = list->next;

					free(list->node);
					free(list);
					node->nFile--;
				}
				else printf("ERROR: Directory is not empty.\n");
				return root;
			}
			lastNode = list;
			list     = list->next;
		}
		list = node->listFile;
	}
	printf("ERROR: No such file or directory.\n");
	return root;
}

void listDirectory(Node *root, char* path)
{
	Node *node;
	List *iterator;

	node = changeDirectory(root,path);
	if(node == NULL)
	{
		printf("ERROR: No such file or Directory.\n");
		return;
	}
	printf("%s: \n",path);
	iterator = node->listDir;
	while(iterator != NULL)
	{
		printf("  %s\n", iterator->node->name);
		iterator = iterator->next;	
	}
	
	iterator = node->listFile;
	while(iterator != NULL)
	{
		printf("  %s\n", iterator->node->name);
		iterator = iterator->next;	
	}
}

void showTree(Node *root)
{
	Queue *q = queueConstructor();
	addQueue(q,root);
	int i=0;
	while(q->head != NULL)
	{
		Node *node = removeQueue(q);
		List *iterator;
		if (strcmp(node->path,"/")) printf("%s/%s:\n",node->path,node->name);
		else						    printf("%s%s:\n",node->path,node->name);
		iterator = node->listDir;
		while(iterator != NULL)
		{
			printf("  %s \n", iterator->node->name);
			addQueue(q,iterator->node);
			iterator = iterator->next;	
		}
	
		iterator = node->listFile;
		while(iterator != NULL)
		{
			printf("  %s \n", iterator->node->name);
			iterator = iterator->next;	
		}
	}
}

