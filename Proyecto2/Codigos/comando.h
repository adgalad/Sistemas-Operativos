//
//  comando.c
//  Shell
//
//  Created by Carlos Spaggiari on 11/14/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

//#include "comando.h"

#ifndef COMANDO
#define COMANDO

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/stat.h>


typedef struct fd_t {
    int pd[2];
    int rs[2];
    int id;
    char *hijo;
    struct fd_t* sig;
    char *path;
}FD;

char **splitStr(char *str, char tok, int *n, char **resultado);


char **interprete(char *comando, int *n, char **res);


char *comando(char *cmd, char **argv, char *output, FD *fm[2], int rs[2]);


const char *infoFile(char *name,char *output);


char *ls(int argc, char **argv,char *output);


char *cat(int argc, char **argv);


char *cp(int argc, char**argv,char *output);


char *find(int argc, char **argv,char *output, FD *fm[2], int rs[2]);


char *rm(int argc,char **argv,char *output);


char *mkdir_(int argc, char **argv,char *output);


char *rmdir_(int argc, char **argv,char *output);

#endif