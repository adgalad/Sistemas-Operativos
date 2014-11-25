

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


FD **crearHijo (int *father, FD *fm[2], int *rs, int root);

void arbolActivo ( int father, FD *fm[2], int rs[2], char **argumentos, char *out, int auxi, int root );

void padre(int rs[2], FD *fm[2], char **argumentos, char *out, int *father, int root);

void hijo(int rs[2], FD *fm[2], int auxi , char ** argumentos, char *out, int *father, int root);

void Handler();

void contador();

void restador();


#endif