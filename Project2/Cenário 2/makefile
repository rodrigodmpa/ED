all: programa limpa

programa: cenario2main.o cenario2.o
	gcc cenario2main.o cenario2.o -o exec

cenario2main.o: cenario2main.c cenario2.c cenario2.h
	gcc -c cenario2main.c

cenario2.o: cenario2.c cenario2.h
	gcc -c cenario2.c

limpa: 
	rm *.o