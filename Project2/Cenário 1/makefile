all: programa limpa

programa: cenario1main.o cenario1.o
	gcc cenario1main.o cenario1.o -o exec

cenario1main.o: cenario1main.c cenario1.c cenario1.h
	gcc -c cenario1main.c

cenario1.o: cenario1.c cenario1.h
	gcc -c cenario1.c

limpa: 
	rm *.o