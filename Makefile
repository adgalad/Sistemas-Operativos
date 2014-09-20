filetree: main.o filetree.o list.o
	gcc -o filetree main.o filetree.o list.o -w
main.o: main.c filetree.h list.h
	gcc -c main.c filetree.c list.c -w
filetree.o: filetree.c filetree.h list.h	
	gcc -c filetree.c list.h -w
list.o: list.c list.h
	gcc -c list.c -w
cleanAll:
	rm *.o filetree
clean:
	rm *.o
