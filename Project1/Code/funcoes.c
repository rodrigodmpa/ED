#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

void checatempo(node *pessoas, int tempo_decorrido) //Checa cada pessoa que ja chamou o elevador e incrementa o tempo de espera
{
	node *aux;
	for(aux = pessoas ; aux != NULL ; aux=aux->prox){
		if(tempo_decorrido > aux->hora_chamada)
			aux->wait_time ++;
	}

}

node *aloca_vetor(node vetor) //Passa os dados do vetor para a lista, alem de alocar a lista
{
	node *novo=(node *) malloc(sizeof(node));
	if(!novo){
		printf("Sem memoria disponivel!\n");
		exit(1);
	}else{
		novo->id = vetor.id;
		novo->andar_inicial = vetor.andar_inicial;
		novo->andar_destino = vetor.andar_destino;
		novo->hora_chamada = vetor.hora_chamada;
		return novo;
	}
}

void insereFim_vetor(node *LISTA,node vetor) //Insere os dados do vetor no fim da lista
{
	node *novo=aloca_vetor(vetor);
	novo->prox = NULL;
	
	if(vazia(LISTA))
		LISTA->prox=novo;
	else{
		node *tmp = LISTA->prox;
		
		while(tmp->prox != NULL)
			tmp = tmp->prox;
		
		tmp->prox = novo;
	}
	tam++;
}

void imprime_lista (node *pessoas, int NPessoas) //Mostra os dados de todos os membros da lista
{
	int i;

	if(vazia(pessoas)){
		printf("Lista vazia!\n\n");
		return ;
	}

	node *aux;
	aux = pessoas->prox;

	printf ("ID\tHora chamada\tAndar Inicial\tAndar Destino\n");

	while (aux != NULL)
	{
		printf ("%d\t", aux->id);
		printf ("%d\t\t", aux->hora_chamada);
		printf ("%d\t\t", aux->andar_inicial);
		printf ("%d\n", aux->andar_destino);
		aux = aux->prox;
	}
	printf("\n");
}



int vazia(node *LISTA) //checa se a lista esta vazia e retorna 1 caso esteja
{
	if(LISTA->prox == NULL)
		return 1;
	else
		return 0;
}

void bubblesort (node *pessoas, int NPessoas) //Organiza o vetor em ordem crescente
{
	int i, j, n;
	node troca;
	n = NPessoas;
	for (i = 0 ; i < ( n - 1 ); i++)
	{
		for (j = 0 ; j < n - i - 1; j++)
		{
      		if (pessoas[j].hora_chamada > pessoas[j+1].hora_chamada)
			{
				troca       = pessoas[j];
				pessoas[j]   = pessoas[j+1];
				pessoas[j+1] = troca;
			}
		}
	}
}


void inicia(node *LISTA) //Inicia a lista com apenas um membro(celula cabeca)
{
	LISTA->prox = NULL;
	tam=0;
}


void libera(node *LISTA) //Desaloca os membros da lista
{
	if(!vazia(LISTA)){
		node *proxNode,
		*atual;
		
		atual = LISTA->prox;
		while(atual != NULL){
			proxNode = atual->prox;				
			free(atual);
			atual = proxNode;
		}
	}
}