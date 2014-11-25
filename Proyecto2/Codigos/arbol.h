

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



void padre(int rs[2], FD *ph, FD *hp,int auxi, char **argumentos, char *out, int father);

void hijo(int rs[2], FD *ph, FD *hp, int auxi , char ** argumentos, char *out, int father);

void childHandler();

#endif
