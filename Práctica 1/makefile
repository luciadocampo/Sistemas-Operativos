ej: shell.o list.o p1.o
	gcc -g p0.o list.o p1.o -lreadline -Wall -o ej
	
shell.o: p0.c
	gcc -g -c p0.c
	
shell2.o: p1.c p1.h
	gcc -g -c p1.c
	
list.o: list.c list.h
	gcc -g -c list.c
	
clc:
	rm *.o ej
	
valgrind: 
	valgrind ./ej
	

