#include "arbol.h"

int main (int argc, char** argv) {

	signal(SIGCHLD, childHandler);
	struct stat inodo;
	int padre;
	DIR *dirp;
	struct dirent *direntp;
	char *ruta;
	pid_t childpid;
	ruta = argv[1];
	padre = -1;
	FD *ph = NULL;
	FD *hp;
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

directorio:

	ph = NULL;

	/** 
	*************
		Cable
	*************
	**/

	if ( padre == 0 ) {
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
		
	printf("ruta actual: %s\n", ruta);

	if ( (dirp = opendir(ruta)) == NULL ) {
		fprintf(stderr, "No se pudo abrir el directorio\n");
		exit(1);
	}




	/**if ( padre == 0 ) {
		printf("pipe: %s %d \n", hp->hijo, auxi);
	}**/

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

					if ( padre != -1 ) {
						close(hp->pd[0]);	// Cierro la tuberia del abuelo
						free(hp);			// Libero la estructura copiada del abuelo
					}

					padre = 0;
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
					//sleep(1);
					close(ph->pd[0]);
				}
			}
		}
		free(aux);
	}
	closedir(dirp);

	if ( padre == -1 ){
		char *sapo = "pokemon ataca";
		int perrito;
		FD *aux_fd;
		aux_fd = ph;
		while( !(aux_fd == NULL) ){
			perrito = write(aux_fd->pd[1], sapo, strlen(sapo)+1);
			aux_fd = aux_fd->sig;
		}
	}
	else {
		int perrito;
		char instruccion[20];
		perrito = read(auxi, instruccion,20);
		printf("%d aca: %s soy %s \n", perrito, instruccion, hp->hijo);
		close(hp->pd[0]);
		FD *aux_fd;
		aux_fd = ph;
		while( !(aux_fd == NULL) ){
			write(aux_fd->pd[1], instruccion, strlen(instruccion)+1);
			aux_fd = aux_fd->sig;
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