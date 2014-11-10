ordenArchivo-t : ordenArchivo-t.o funciones.o
		gcc -o ordenArchivo-t ordenArchivo-t.o funciones.o -lpthread -w
ordenArchivo-t.o : ordenArchivo-t.c	funciones.c
		gcc -c ordenArchivo-t.c	funciones.c -lpthread -w
funciones.o : funciones.c funciones.h
		gcc -c funciones.c	funciones.h -lpthread -w

cleanAll : rm *.o
