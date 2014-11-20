//
//  comando.c
//  fssh
//
//  Created by Carlos Spaggiari on 11/18/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#include "comando.h"

char** splitStr(char *str, char tok, int *n){
    char **resultado = (char **)malloc(3*6);
    int i,j=0;
    resultado[j++] = str;
    for (i = 0; str[i]!='\0'; i++) {
        if (str[i] == tok) {
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
    else if (resultado[1][0]!='/') {
        char *aux = malloc(strlen(resultado[1])+1);
        sprintf(aux, "/%s",resultado[1]);
        free(resultado[1]);
        resultado[1] = aux;
    }
    return resultado;
}

char **interprete(char *comando, int *n){
    char **res = splitStr(comando,' ',n);

    if (!strcmp(res[0], "cp") ||
        !strcmp(res[0], "mv") ||
        !strcmp(res[0], "rm") ||
        !strcmp(res[0], "cat")||
        !strcmp(res[0], "ls")
        )
    {
        char *c = malloc(32);
        strcpy(c,".");
        strcat(c,res[1]);
        DIR *dir = opendir(c);
        if (dir == NULL) {
            int i;
            for( i = (int)strlen(res[1]) -1 ; res[1][i] != '/' && i > 0 ; i--);
            res[1][i] = '\0';
            res[(*n)++] = &res[1][i+1];
        }
        else if (strcmp(res[0], "ls")){
            *n = 0;
            return res;
        }
        closedir(dir);
    }
    
    return res;
}


const char *infoFile(struct stat *s, char *name){
    char *buffer = malloc(80);
    char *fecha  = malloc(30);
    mode_t modo  = s->st_mode;
    char tipo    = '-';

    struct passwd *pw = getpwuid(s->st_uid);
    struct group  *gr = getgrgid(s->st_gid);
    struct tm *tm;
    time_t time;
    time = s->st_mtimespec.tv_sec;
    tm   = localtime(&time);
    
    strftime(fecha, sizeof fecha, "%Y-%m-%d %H:%M:%S", tm);
    
    if (S_ISLNK(modo))  tipo = 'l';
    else if (S_ISDIR(modo))  tipo = 'd';
    else if (S_ISBLK(modo))  tipo = 'b';
    else if (S_ISCHR(modo))  tipo = 'c';
    else if (S_ISFIFO(modo)) tipo = '|';
    
    sprintf(buffer, "%c%c%c%c%c%c%c%c%c%c %d %s %s %lli %s %s",
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
            s->st_nlink ,
            pw->pw_name ,
            gr->gr_name ,
            s->st_size,
            fecha,
            name);

    return (const char*) buffer;
}

char *ls(int argc, char **argv){
    char *c = malloc(20);
    strcpy(c,".");
    strcat(c, argv[1]);
    char *buffer = malloc(1024);

    if (argc == 3){
        strcat(c, "/");
        strcat(c, argv[2]);
        struct stat s;
        if(stat(c,&s) != 0){
            sprintf(buffer,"No such file\n");
            return buffer;
        }
        
        sprintf(buffer,"%s\n", infoFile(&s, argv[2]));
    }
    else {
        DIR *directorio = opendir(c);
        struct dirent *d;
        char *path = malloc(20);
        strcpy(path,c);
        strcat(path,"/");
        strcpy(buffer,"");
        while ((d = readdir(directorio)) != NULL)
        {
            if (d->d_name[0] != '.') {
                strcpy(c,path);
                strcat(c, d->d_name);
                struct stat *s =(struct stat*) malloc(sizeof(struct stat));
                stat(c,s);
                strcat(buffer,infoFile(s, d->d_name));
                strcat(buffer, "\n");
            }
        }
        closedir(directorio);
    }
    return buffer;
}


char* cat(int argc, char **argv){
    char *c = malloc(20);
    sprintf(c,".%s/%s",argv[1],argv[2]);
    FILE *file = fopen(c, "rb");
    
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
    strcat(contenido,"\n");
    return contenido;
}

char *cp(int argc, char**argv){
    char *buffer = malloc(128);
    char **arg = (char **) malloc(sizeof(char*)*3);
    arg[0] = argv[0];
    arg[1] = argv[1];
    arg[2] = argv[3];
    char *contenido = cat(3,arg);
    if (contenido == NULL) {
        sprintf(buffer, "-fssh: %s/%s: No existe el archivo\n",arg[1],arg[2]);
        return buffer;
    }
    char *c = malloc(100);
    sprintf(c, ".%s",argv[2]);
    DIR *directorio = opendir(c);
    if (directorio != NULL) {
        strcat(c, "/");
        strcat(c, argv[3]);
    }
    FILE *file = fopen(c, "w");
    if (file == NULL) {
        sprintf(buffer, "-fssh: %s: No existe el archivo o directorio\n",c);
        return buffer;
    }
    fwrite(contenido, 1, strlen(contenido), file);
    fclose(file);
    return "";
}

char *rm(int argc,char **argv){
    char *c = malloc(100);
    
    sprintf(c,".%s/%s",argv[1],argv[2]);
    
    if (remove(c) == -1)
    {
        char *buffer = malloc(128);
        sprintf(buffer, "-fssh: %s: No existe el archivo\n",c);
        return buffer;
    }
    
    return "";
}

char *mkdir_(int argc, char **argv){
    char *c = malloc(100);
    sprintf(c,".%s",argv[1]);
    printf("%s\n",c);
    DIR *dir = opendir(c);
    if ( dir != NULL) {
        char *buffer = malloc(128);
        sprintf(buffer, "-fssh: %s: Ya existe el directorio\n",c);
        closedir(dir);
        return buffer;
    }
    closedir(dir);
    mkdir(c, 0755);
    return "";
}

char *rmdir_(int argc, char **argv){
    char *c = malloc(100);
    sprintf(c, ".%s",argv[1]);
    DIR *dir = opendir(c);
    if ( dir == NULL) {
        char *buffer = malloc(128);
        sprintf(buffer, "-fssh: %s: No existe el directorio\n",c);
        closedir(dir);
        return buffer;
    }
    struct dirent *d;
    while ((d = readdir(dir)) != NULL){
        if (d->d_name[0] != '.') {
            char *buffer = malloc(128);
            sprintf(buffer, "-fssh: %s: El directorio no esta vacio\n",c);
            closedir(dir);
            return buffer;
        }
    }
    closedir(dir);
    if (rmdir(c) < 0) printf("-fssh: %s El directorio no pudo ser borrado\n",c);
    return "";
}

char *comando(char *cmd){
    int argc=0;
    char **argv = interprete(cmd, &argc);
    char *buffer = malloc(100);
    strcpy(buffer, "");
    if (argc > 0) {
        if(!strcmp(argv[0], "ls")) {
            strcpy(buffer,ls(argc, argv));
        }
        else if(!strcmp(argv[0], "cat")) {
            buffer = cat(argc, argv);
            if(buffer == NULL) {
                buffer = malloc(100);
                sprintf(buffer,"-fssh: %s: No existe el archivo\n",argv[2]);
            }
        }
        else if(!strcmp(argv[0], "cp")) {
            strcpy(buffer, cp(argc, argv));
        }
        else if(!strcmp(argv[0], "mv")) {
            
        }
        else if(!strcmp(argv[0], "find")) {
            
        }
        else if(!strcmp(argv[0], "rm")) {
            strcpy(buffer, rm(argc, argv));
        }
        else if(!strcmp(argv[0], "mkdir")) {
            strcpy(buffer, mkdir_(argc, argv));
        }
        else if(!strcmp(argv[0], "rmdir")) {
            strcpy(buffer,rmdir_(argc, argv));
        }
        else if(!strcmp(argv[0], "quit")) {
            exit(0);
        }
    }
    else {
        sprintf(buffer, "-fssh: %s: Es un directorio\n",argv[1]);
    }
    return buffer;
}
