filetree: main.o archivo.o cola.o
		gcc -o filetree main.o archivo.o cola.o -w
main.o:	main.c archivo.h cola.h
		gcc -c main.c archivo.c cola.c -w
archivo.o:	archivo.c archivo.h cola.h
		gcc -c archivo.c cola.h -w
cola.o:	cola.c cola.h
		gcc -c cola.c -w
cleanAll:
		rm *.o filetree
clean:	
		rm *.o


 