
#include "arbol.h"
#include "comando.h"

int main (int argc, char** argv) {

	signal(SIGCHLD, childHandler);
	struct stat inodo;
	int father;
	DIR *dirp;
	struct dirent *direntp;
	char *ruta = argv[1];
	pid_t childpid;
	father = -1;
	FD *ph = NULL;
	FD *hp;
	int rs[2];
	int auxi;

	if (stat(ruta, &inodo) == -1 ) {
		fprintf(stderr, "No se pudo aplicar stat sobre el archivo %s: %s \n"
			,ruta, strerror(errno));
		exit(1);
	}
	if ( !(inodo.st_mode & S_IFDIR) ) {
		fprintf(stderr, "La ruta especificada no es un Directorio\n");
		exit(1);
	}

	pipe(rs);

directorio:

	ph = NULL;

	/** 
	*************
		Cable
	*************
	**/

	if ( father == 0 ) {
		auxi = hp->pd[0];
	}


	/**	 
	******************************************************
		Imprimimos la Ruta actual y la modificamos para
		 que pueda ser interpretada como ruta absoluta
	******************************************************
	**/

	if ( ! (ruta[strlen(ruta)-1] == '/') ){
		strcat(ruta,"/");
	}
		
	//printf("ruta actual: %s\n", ruta);

	if ( (dirp = opendir(ruta)) == NULL ) {
		fprintf(stderr, "No se pudo abrir el directorio\n");
		exit(1);
	}


	/** 
	****************************************************
		Buscamos en la tabla de inodos del directorio
	****************************************************
	**/

skip:
	while (( direntp = readdir(dirp)) != NULL ) {
		if ( !strcmp(direntp->d_name, ".") || !strcmp(direntp->d_name, "..") ) {
			goto skip;
		}

		/**
		***********************************************************
			 Construccion de la ruta absoluta del subdirectorio
		***********************************************************
		**/

		char *aux = (char *)malloc(strlen(ruta) + strlen(direntp->d_name) + 1);
		strcpy(aux,ruta);
		strcat(aux,direntp->d_name);


		if (stat(aux, &inodo) == -1 ) {
			fprintf(stderr, "No se pudo aplicar stat sobre el archivo %s: %s \n"
				,aux, strerror(errno));
			exit(1);
		}
		else {
			if ( inodo.st_mode & S_IFDIR ) {
				/**
				***********************************************************
					Estructura auxiliar para comunicacion con los hijos
				***********************************************************
				**/

				FD *ph_aux = (FD *)malloc(sizeof(FD));
				pipe(ph_aux->pd);
				ph_aux->hijo = direntp->d_name;
				ph_aux->sig = ph;
				ph = ph_aux;
				
				if ( (childpid = fork()) == 0 )  {
					ruta = aux;

					if ( father != -1 ) {
						father = 0;
						close(hp->pd[0]);	// Cierro la tuberia del abuelo
						free(hp);			// Libero la estructura copiada del abuelo
						close(rs[0]);		// Cierro la tuberia de lectura para resultado
					}

					father = 0;
					hp = ph;
					close(hp->pd[1]);
					ph = ph->sig;

					/**
					 *********************************************************
						Limpieza de la estructura de hijos copiada del padre
					 *********************************************************
					**/
					while( !(ph == NULL) ){
						FD *aux_fd;
						aux_fd = ph;
						ph = aux_fd->sig;
						free(aux_fd);
					}

					goto directorio;

				}
				else {
					close(ph->pd[0]);
				}
			}
		}
		free(aux);
	}
	closedir(dirp);



	/** 
	*****************************************
			Entrada de Comandos
	*****************************************
	**/

prompt1:

	if ( father == -1 ){
		char lectura[100];
		char tokken[100];
		char resultado[1000];
		char *direccion;
		int status;
shell:	printf("fssh$ ");
		fgets(lectura,100, stdin);
		if ( !strcmp(lectura, "\n") ) {
			printf("\n");
			goto shell;
		}
		FD *aux_fd;

		if ( lectura[strlen(lectura)-1] == '\n' ){
			lectura[strlen(lectura)-1] = '\0';
		}

		/**
		***************************************************************
			Cierre de todos los Pipes y terminacion del proceso raiz
		***************************************************************
		**/

		if ( !strcmp(lectura, "exit") ){
			aux_fd = ph;
			while ( aux_fd != NULL ) {
				ph = aux_fd->sig;
				close(aux_fd->pd[1]);
				free(aux_fd);
				aux_fd = ph;
				exit(0);
			}
		}

		strcpy(tokken, lectura);
		direccion = strtok(tokken, "\ ");
		direccion = strtok(NULL,"\ ");
		direccion = strtok(direccion, "/");

		if ( direccion == NULL || !strcmp(direccion,"/")) {
			// Ejecutar Instruccion
			char *out = comando(lectura);
			write(rs[1],out, strlen(out)+1);
			goto resul;
		}
			
		aux_fd = ph;
		while ( strcmp(aux_fd->hijo, direccion) ){
				aux_fd = aux_fd->sig;				
				if ( aux_fd == NULL ){
					printf("La ruta del comando no existe\n");
					goto prompt1;
		}
	}
		write(aux_fd->pd[1], lectura, strlen(lectura)+1);
resul:	read(rs[0], resultado,1000);
		printf("%s\n", resultado);
		goto prompt1;
	}
	else { 
		/** 
		*****************************************
			   Comunicacion entre procesos
		*****************************************
		**/

		int status;
		status = 420;
		char instruccion[100];
		
prompt2:
		while ( status != 0 ){
			int aux1, aux2;
			FD *aux_fd;
			status = read(auxi, instruccion,100);
			char *tokken;
			char *direccion;
			char *direccion1;
			tokken = malloc(sizeof(instruccion)+1);


			strcpy(tokken, instruccion);
			direccion = strtok(tokken, "\ ");
			direccion = strtok(NULL,"\ ");
			// meter un if si es un comando de manipulacion de archivos
			// necesito una nueva variable local para saber que es un comando para archivos
			direccion = strtok(direccion, "/");

			aux1 = 0;
			while ( strcmp(direccion, hp->hijo) ) {
				direccion = strtok(NULL, "/");
				aux1++;
			}
			direccion = strtok(NULL, "/");
			aux1++;

			strcpy(tokken, instruccion);
			direccion1 = strtok(tokken, "\ ");
			direccion1 = strtok(NULL,"\ ");
			direccion1 = strtok(direccion1, "/");

			aux2 = 0;
			while ( direccion1 != NULL ) {
				direccion1 = strtok(NULL, "/");
				aux2++;
			}
			
			if ( aux1 == aux2 ) {
				// Ejecutar Instruccion
				char *out = comando(instruccion);
				write(rs[1],out, strlen(out)+1);
			}
			else {
				aux_fd = ph;
				while ( strcmp(aux_fd->hijo, direccion) ){
						aux_fd = aux_fd->sig;				
						if ( aux_fd == NULL ){
							printf("La ruta del comando no existe\n");
							goto prompt2;
						}
				}
				write(aux_fd->pd[1], instruccion, strlen(instruccion)+1);
			}
			free(tokken);
		}

	} 
	FD *aux_fd;
	aux_fd = ph;
	while( !(aux_fd == NULL) ){
		close(aux_fd->pd[1]);
		aux_fd = aux_fd->sig;
		free(ph);
		ph = aux_fd;
	}
	exit(0);

}

/**
 *****************************************
	Manejador de señales para los hijos.
 *****************************************
 **/

void childHandler () {
	int childPid, childStatus;
	childPid = wait(&childStatus);
	printf("El hijo %d termino\n",childPid);
}
