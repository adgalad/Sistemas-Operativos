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
	FD hp;
	int ph_pd[2];
	int hp_pd[2];
	char *instruccion;

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

	/**
	************************
		Pipe de Padre a Hijo
			(Escritura) 
	************************
	**/

	pipe(ph_pd);
	close(ph_pd[0]);

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
			Estructura auxiliar para determinar que hijo va a leer 
								por el pipe 
		***********************************************************
		**/
		FD *ph_aux = (FD *)malloc(sizeof(FD));
		ph_aux->pd = 0;
		ph_aux->hijo = direntp->d_name;
		ph_aux->sig = ph;
		ph = ph_aux;

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
				if ( (childpid = fork()) == 0 )  {
					ruta = aux;
					padre = 0;
					hp = *ph;
					hp_pd[0] = ph_pd[0];
					hp_pd[1] = ph_pd[1];
					ph_pd[0] = NULL;
					ph_pd[1] = NULL;
					close(hp_pd[1]);

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
					if ( padre == -1 ){
						//raiz de los directorios
					}
					else {
						while( !hp.pd );
						read(ph_pd[1], instruccion, 100);
						// hacer cosas //
					}
				}
			}
		}
		free(aux);
	}

	close(ph_pd[1]);
	closedir(dirp);
	exit(0);

}

void childHandler () {
	int childPid, childStatus;
	childPid = wait(&childStatus);
	printf("El hijo %d termino\n",childPid);
}