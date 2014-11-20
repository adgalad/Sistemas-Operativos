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


char **splitStr(char *str, char tok, int *n);


char **interprete(char *comando, int *n);


char *comando(char *cmd);


const char *infoFile(struct stat *s, char *name);


char *ls(int argc, char **argv);


char *cat(int argc, char **argv);


char *cp(int argc, char**argv);


char *rm(int argc,char **argv);


char *mkdir_(int argc, char **argv);


char *rmdir_(int argc, char **argv);