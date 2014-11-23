//
//  comando.c
//  Shell
//
//  Created by Carlos Spaggiari on 11/14/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

//#include "comando.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/stat.h>


char **splitStr(char *str, char tok, int *n, char **resultado);


char **interprete(char *comando, int *n, char **res);


char *comando(char *cmd, char **argv, char *buffer);


const char *infoFile(char *name,char *buffer);


char *ls(int argc, char **argv,char *buffer);


char *cat(int argc, char **argv);


char *cp(int argc, char**argv,char *buffer);


char *find(int argc, char **argv,char *buffer);


char *rm(int argc,char **argv,char *buffer);


char *mkdir_(int argc, char **argv,char *buffer);


char *rmdir_(int argc, char **argv,char *buffer);