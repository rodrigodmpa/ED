#include <stdio.h>
#include <stdlib.h>

typedef struct Celula_str *Apontador;

typedef struct Celula_str
{
    int chave;
    int Indice;
    Apontador Prox,Ant;
} Celula;

typedef struct
{
    Apontador Primeiro, Ultimo;
} TipoLista;

void FLVazia(TipoLista *Lista);

int Vazia(TipoLista Lista);

void Insere(int x, TipoLista *Lista);

void ImprimeListaNoArquivo(TipoLista Lista,FILE *fp);

void EncheLista(TipoLista *Lista, int N, int semente);

void EncheVetor(int *Vetor, int N, int semente);

void quick_vetor(int *Vetor,int comeco, int fim, int *Contador);

void quick_lista(TipoLista *Lista, int comeco, int fim, Apontador Auxi, int *Contador);

int mediana_vetor(int *Vetor,int i,int j);

int mediana_lista(TipoLista *Lista,int i, int j,Apontador Auxi, Apontador Auxj);

void ZeraLista(TipoLista *lista);

void DeletaLista(TipoLista *lista);

void ImprimeVetorNoArquivo(int *Vetor,FILE *fp, int N);