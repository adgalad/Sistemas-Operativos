

#ifndef ARBOL
#define ARBOL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <signal.h>
#include "comando.h"


typedef struct fd_t {
	int pd[2];
	int rs[2];
	int id;
	char *hijo;
	struct fd_t* sig;
}FD;

void crearHijo (int *father, FD *ph, FD *hp, int *rs);

void arbolActivo ( int father, FD *ph, FD *hp, int rs[2], char **argumentos, char *out, int auxi );

void padre(int rs[2], FD *ph, FD *hp, char **argumentos, char *out, int *father);

void hijo(int rs[2], FD *ph, FD *hp, int auxi , char ** argumentos, char *out, int *father);

void Handler();


#endif