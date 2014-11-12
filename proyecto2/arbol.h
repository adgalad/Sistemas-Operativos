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


#ifndef ARBOL
#define ARBOL


typedef struct fd_t {
	int pd[2];
	int rs[2];
	char *hijo;
	struct fd_t* sig;
}FD;

void childHandler();

#endif