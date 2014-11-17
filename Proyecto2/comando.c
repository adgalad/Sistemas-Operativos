//
//  comando.c
//  Shell
//
//  Created by Carlos Spaggiari on 11/14/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#include "comando.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


char** splitStr(char *str, char tok, int *n)
{
    char **resultado = (char **) malloc(sizeof(char*)*6);
    int i;
    *n = 0;
    resultado[*n++] = str;
    for (i = 0; str[i]!='\0'; i++) {
        if (str[i] == tok) {
            str[i++] = '\n';
            resultado[*n++] = str+i;
        }
    }
    return resultado;
}

char **interprete(char *comando)
{
    char **resultado = (char **) malloc(sizeof(char*)*6);
    
    return resultado;
}