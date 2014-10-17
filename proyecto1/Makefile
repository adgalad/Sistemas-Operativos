odenArchivo-p: ordenArchivo-p.o archivo.o 
	gcc -o ordenArchivo-p ordenArchivo-p.o archivo.o 
ordenArchivo-p.o: ordenArchivo-p.c archivo.h
	gcc -c ordenArchivo-p.c archivo.c
hoja: hoja.o archivo.o
	gcc -o hoja hoja.o archivo.o
hoja.o: hoja.c archivo.h
	gcc -c hoja.c archivo.c
archivo.o: archivo.c archivo.h	
	gcc -c archivo.c archivo.h 

cleanAll:
	rm *.o filetree
clean:
	rm *.o
