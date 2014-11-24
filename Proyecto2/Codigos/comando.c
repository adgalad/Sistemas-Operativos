//
//  comando.c
//  fssh
//
//  Created by Carlos Spaggiari on 11/18/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#include "comando.h"

char** splitStr(char *str, char tok, int *n, char **resultado){
    int i,j=0;
    resultado[j++] = str;
    for (i = 0; str[i]!='\0'; i++) {
        if (str[i] == tok ) {
            str[i++] = '\0';
            resultado[j++] = str+i;
        }
        else if (str[i] == '\n') str[i++] = '\0';
    }
    *n = j;
    if (resultado[1] == NULL){
        resultado[1] = malloc(1);
        strcpy(resultado[1], "/");
    }
    else if (!strcmp(resultado[1], "\0")){
        strcpy(resultado[1],"/");
    }
    else if (resultado[1]!=NULL && resultado[1][0]!='/') {
        char *aux = malloc(strlen(resultado[1])+1);
        sprintf(aux, "/%s",resultado[1]);
        resultado[1] = aux;
    }
    return resultado;
}

char **interprete(char *comando, int *n, char **res){
    splitStr(comando,' ',n,res);
    
    if (!strcmp(res[0], "cp") ||
        !strcmp(res[0], "mv") ||
        !strcmp(res[0], "rm") ||
        !strcmp(res[0], "cat")||
        !strcmp(res[0], "ls")
        )
    {
        char *c = (char*)malloc(32);
        strcpy(c,".");
        strcat(c,res[1]);
        DIR *dir = opendir(c);
        free(c);
        if (dir == NULL) {
            int i;
            for( i = (int)strlen(res[1]) -1 ; res[1][i] != '/' && i > 0 ; i--);
            res[1][i] = '\0';
            res[(*n)++] = &res[1][i+1];
            return res;
        }
        else if (strcmp(res[0], "ls")){
            *n = 0;
            return res;
        }
        closedir(dir);
        
    }
    
    return res;
}


const char *infoFile(char *name, char *output){
    struct stat s;
    stat(name, &s);
    char fecha[100];
    mode_t modo  = s.st_mode;
    char tipo    = '-';
    
    strcpy(fecha,ctime(&s.st_mtime));
    fecha[strlen(fecha)-1] = ' ';
    if (S_ISLNK(modo))  tipo = 'l';
    else if (S_ISDIR(modo))  tipo = 'd';
    else if (S_ISBLK(modo))  tipo = 'b';
    else if (S_ISCHR(modo))  tipo = 'c';
    else if (S_ISFIFO(modo)) tipo = '|';
    
    sprintf(output, "%c%c%c%c%c%c%c%c%c%c %d %s %s %lli %s",
            tipo,
            modo & 256 ? 'r' : '-',
            modo & 128 ? 'w' : '-',
            modo &  64 ? 'x' : '-',
            modo &  32 ? 'r' : '-',
            modo &  16 ? 'w' : '-',
            modo &   8 ? 'x' : '-',
            modo &   4 ? 'r' : '-',
            modo &   2 ? 'w' : '-',
            modo &   1 ? 'x' : '-',
            s.st_nlink ,
            getpwuid(s.st_uid)->pw_name ,
            getgrgid(s.st_gid)->gr_name ,
            s.st_size,
            fecha);
    return (const char*) output;
}

char *ls(int argc, char **argv, char *output){
    char *c = malloc(20);
    strcpy(c,".");
    strcat(c, argv[1]);    
    if (argc == 3){
        strcat(c, "/");
        strcat(c, argv[2]);
        struct stat s;
        if(stat(c,&s) != 0){
            sprintf(output,"-fssh: %s/%s: No existe el archivo o directorio\n"
                    ,argv[1],argv[2]);
            free(c);
            return "";
        }
        sprintf(output,"%s%s\n", infoFile(c,output),argv[2]);
    }
    else {
        DIR *directorio = opendir(c);
        if (directorio != NULL) {
            struct dirent *d;
            char *path = malloc(20);
            strcpy(path,c);
            strcat(path,"/");
            
            strcpy(output,"");
            while ((d = readdir(directorio)) != NULL)
            {
                if (d->d_name[0] != '.') {
                    char *b = malloc(100);
                    strcpy(c,path);
                    strcat(c, d->d_name);
                    strcat(output,infoFile(c,b));
                    strcat(output, d->d_name);
                    strcat(output, "\n");
                }
            }
            closedir(directorio);
            
        }
    }
    free(c);
    return output;
}


char* cat(int argc, char **argv){
    char *c = malloc(20);
    sprintf(c,".%s/%s",argv[1],argv[2]);
    FILE *file = fopen(c, "rb");
    free(c);
    if (file == NULL) {
        return NULL;
    }
    
    fseek(file, 0L, SEEK_END);
    long int fileSize = ftell(file);
    fseek(file, 0L, SEEK_SET);
    
    char *contenido = malloc(fileSize);
    contenido = malloc(fileSize+1);
    fread(contenido,1,fileSize,file);
    fclose(file);
    if (strlen(contenido) != 0 && contenido[strlen(contenido)-1]!='\n')
        strcat(contenido,"\n");
    return contenido;
}

char *cp(int argc, char**argv,char *output){
    char **arg = (char **) malloc(sizeof(char*)*3);
    arg[0] = argv[0];
    arg[1] = argv[1];
    arg[2] = argv[3];
    char *contenido = cat(3,arg);
    if (contenido == NULL) {
        sprintf(output, "-fssh: %s/%s: No existe el archivo\n",arg[1],arg[2]);
        free(arg);
        return output;
    }
    free(arg);
    char *c = malloc(100);
    sprintf(c, ".%s",argv[2]);
    DIR *directorio = opendir(c);
    if (directorio != NULL) {
        strcat(c, "/");
        strcat(c, argv[3]);
    }
    FILE *file = fopen(c, "w");
    if (file == NULL) {
        sprintf(output, "-fssh: %s: No existe el archivo o directorio\n",c);
        return output;
    }
    fwrite(contenido, 1, strlen(contenido), file);
    fclose(file);
    return "";
}

char *find(int argc, char **argv,char *output){
    char *c = malloc(100);
    sprintf(c, ".%s",argv[1]);
    
    DIR *dir = opendir(c);
    if (dir != NULL) {
        struct dirent *d;
        strcpy(output,"");
        while ((d=readdir(dir)) != NULL) {
            if (d->d_name[0] != '.') {
                strcat(output, strstr(d->d_name, argv[2]));
                strcat(output, "\n");
            }
        }
        free(c);
        return output;
    }
    free(c);
    return "";
}

char *rm(int argc,char **argv,char *output){
    char *c = malloc(100);
    
    sprintf(c,".%s/%s",argv[1],argv[2]);
    
    if (remove(c) == -1)
    {
        sprintf(output, "-fssh: %s: No existe el archivo\n",c);
        free(c);
        return output;
    }
    free(c);
    return "";
}

char *mkdir_(int argc, char **argv, char *output){
    char *c = malloc(100);
    sprintf(c,".%s",argv[1]);
    DIR *dir = opendir(c);
    if ( dir != NULL) {
        sprintf(output, "-fssh: %s: Ya existe el directorio\n",c);
        closedir(dir);
        free(c);
        return output;
    }
    if ( mkdir(c, 0755) == -1 ) {
        sprintf(output, "-fssh: %s: No se pudo crear el directorio\n",c);
    }

    free(c);
    sprintf(output,"0");
    return "";
}

char *rmdir_(int argc, char **argv, char *output){
    char *c = malloc(100);
    sprintf(c, ".%s",argv[1]);
    DIR *dir = opendir(c);
    if ( dir == NULL) {
        sprintf(output, "-fssh: %s: No existe el directorio\n",argv[1]);
        closedir(dir);
        free(c);
        return output;
    }
    struct dirent *d;
    while ((d = readdir(dir)) != NULL){
        if (d->d_name[0] != '.') {
            char *output = malloc(128);
            sprintf(output, "-fssh: %s: El directorio no esta vacio\n",argv[1]);
            closedir(dir);
            free(c);
            //free(d);
            return output;
        }
    }
    closedir(dir);
    if (rmdir(c) < 0) {
        sprintf(output,"-fssh: %s El directorio no pudo ser borrado\n",argv[1]);
        return output;
    }
    free(c);
    free(d);
    sprintf(output,"0");
    return "";
}

char *comando(char *cmd, char **argv, char* output){
    int argc=0;
    interprete(cmd, &argc, argv);
    strcpy(output, "");
    
    if (argc > 0) {
        if(!strcmp(argv[0], "ls")) {
            ls(argc, argv,output);
        }
        else if(!strcmp(argv[0], "cat")) {
            char *c = cat(argc, argv);
            if(c == NULL) {
                sprintf(output,"-fssh: %s/%s: No existe el archivo\n",
                        argv[1],argv[2]);
            }
            else {
                strcpy(output,c);
            }
        }
        else if(!strcmp(argv[0], "cp")) {
            cp(argc, argv,output);
        }
        else if(!strcmp(argv[0], "mv")) {
            
        }
        else if(!strcmp(argv[0], "find")) {
            
        }
        else if(!strcmp(argv[0], "rm")) {
            rm(argc, argv,output);
        }
        else if(!strcmp(argv[0], "mkdir")) {
            mkdir_(argc, argv,output);
        }
        else if(!strcmp(argv[0], "rmdir")) {
            output = rmdir_(argc, argv,output);
        }
        else if(!strcmp(argv[0], "quit")) {
            exit(0);
        }
        else {
            sprintf(output,"-fssh: %s: No existe el comando\n",argv[0]);
        }
    }
    else {
        sprintf(output, "-fssh: %s: Es un directorio\n",argv[1]);
    }

    return output;
}