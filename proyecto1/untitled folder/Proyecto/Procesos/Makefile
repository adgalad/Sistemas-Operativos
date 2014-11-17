fssh: main.o Shell.o Lista.o
	gcc -o fssh main.o Lista.o Shell.o  

main.o: main.c Shell.h Lista.h
	gcc -c main.c Shell.c Lista.c
Shell.o: Shell.c Shell.h Lista.h
	gcc -c Shell.c Shell.h Lista.h
Lista.o: Lista.c Lista.h	
	gcc -c Lista.c Lista.h 

cleanAll:
	rm *.o ordenArchivo-p
clean:
	rm *.o
