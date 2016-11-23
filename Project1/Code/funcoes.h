#include <stdio.h>
#include <stdlib.h>


struct Node{
	int id; //Numero que identifica cada pessoa
	int hora_chamada; //Hora em que o elevador eh chamado
	int andar_destino; //Andar que a pessoa deseja chegar
	int andar_inicial; //Andar em que a pessoa chama o elevador
	int wait_time; //Tempo de espera
	struct Node *prox; //Ponteiro que aponta para o proximo membro da lista
}; 
typedef struct Node node;

int tam;

void inicia(node *LISTA);
node *aloca();
void libera(node *LISTA);

void bubblesort (node *, int );
void imprime_lista (node *, int NPessoas);
node *aloca_vetor(node vetor);

void insereFim_vetor(node *LISTA,node vetor);
void checatempo(node *pessoas, int tempo_decorrido);