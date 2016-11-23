all: programa limpa

programa: main.o funcoes.o
	gcc main.o funcoes.o -o elevador

main.o: main.c funcoes.c funcoes.h
	gcc -c main.c

funcoes.o: funcoes.c funcoes.h
	gcc -c funcoes.c

limpa: 
	rm *.o
