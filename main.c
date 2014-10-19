
#include <stdlib.h>
#include <stdio.h>
#include "filetree.h"

int main(int argc, char **argv)
{
	FILE* f;
	char *command,*name;
	//f = fopen(argv[1],"r");
	command = malloc(255);
	name = malloc(255);
	Node *root = newNode("","",DIRECTORY, NULL),
		 *dir  = root;
	while(scanf("%s %s",command,name)!=EOF)
	{
		if (strcmp(command,"md") == 0)
		{
			dir = newFile(dir,name,DIRECTORY);
		}
		else if (strcmp(command,"ma") == 0)
		{
			dir = newFile(dir,name,FILES);	
		}
		else if (strcmp(command,"rm") == 0)
		{
			dir = removeFile(dir,name);
		}
		else if (strcmp(command,"ls") == 0)
		{
			listDirectory(dir,name);
		}
		else if (strcmp(command,"cd") == 0)
		{
			dir = changeDirectory(dir,name);
		}
		else printf("Command \"%s\" not found.\n",command); 
	}

	printf("\n BFS of root directory:\n");
	showTree(root);
	//fclose(f);

	return 0;
}
