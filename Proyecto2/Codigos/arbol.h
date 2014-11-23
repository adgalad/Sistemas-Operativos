

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
	char *hijo;
	struct fd_t* sig;
}FD;

void padre(int rs[2], FD *ph, char **argumentos, char *out);

void hijo(int rs[2], FD *ph, FD *hp, int auxi , char ** argumentos, char *out);

void childHandler();

#endif