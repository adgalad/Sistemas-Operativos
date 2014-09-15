
#include <stdlib.h>
#include <stdio.h>
#include "filetree.h"

int main(int argc, char **argv)
{
	FILE* f;
	char *command,*name;

	f = fopen(argv[1],"r");
	command = malloc(255);
	name = malloc(255);
	Node *root = newNode("","",DIRECTORY);
	while(fscanf(f,"%s %s",command,name)!=EOF)
	{
		if (strcmp(command,"md") == 0)
		{
			root = newFile(root,name,DIRECTORY);
		}
		else if (strcmp(command,"ma") == 0)
		{
			root = newFile(root,name,FILES);	
		}
		else if (strcmp(command,"rm") == 0)
		{
			root = removeFile(root,name);
		}
		else if(strcmp(command,"ls") == 0)
		{
			listDirectory(root,name);
		}
	}

	printf("\n BFS of root directory: \n");
	showTree(root);
	fclose(f);

	return 0;
}
