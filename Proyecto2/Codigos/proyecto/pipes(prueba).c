#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>


int  pd[2], n, p, sapo[2];
char linea[15], *s="datos desde el pipe";

int main(int argc, char *argv[])
{
  p = getpid();
  printf("Padre = %d\n", p);

  pipe(pd);
  sapo[0] = pd[0];
  sapo[1] = pd[1];
  if (fork()) {
    printf("Padre %d cierra pd[0]\n", p);
    close(pd[0]);

    while(1) {
      printf("Padre %d escribe pipe : %s\n", p, s);
      write(sapo[1], s, strlen(s)+1);
    }
  }
  else{
    p = getpid();
    printf("Hijo  %d cierra pd[1]\n", p);
    close(pd[1]);
    
    while(1){
      printf("Hijo  %d lee del pipe : ", p);
      n = read(sapo[0], linea, 15);      
      linea[n]=0;
      printf("%s\n", linea);
  	}
  }
}
