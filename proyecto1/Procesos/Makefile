odenArchivo-p: ordenArchivo-p.o funciones.o 
	gcc -o ordenArchivo-p ordenArchivo-p.o funciones.o 
ordenArchivo-p.o: ordenArchivo-p.c funciones.h
	gcc -c ordenArchivo-p.c funciones.c
funciones.o: funciones.c funciones.h	
	gcc -c funciones.c funciones.h 

cleanAll:
	rm *.o filetree
clean:
	rm *.o
