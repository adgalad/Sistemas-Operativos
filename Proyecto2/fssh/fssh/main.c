//
//  comando.c
//  Shell
//
//  Created by Carlos Spaggiari on 11/14/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

//#include "comando.h"

#include "comando.h"

int main(int argc, char **argv){

    if (argc == 1) chdir("/Users/carlosspaggiari");
    else chdir(argv[1]);
    char *str = malloc(1024);
    while (1) {
        printf("fssh-1.1$ ");
        fgets(str, 128, stdin);
        printf("%s",comando(str, 1));
    }
}