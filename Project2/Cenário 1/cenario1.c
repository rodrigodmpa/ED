#include <stdio.h>
#include <stdlib.h>
#include "cenario1.h"


void FLVazia(TipoLista *Lista)
{
    Lista->Primeiro = (Apontador) malloc(sizeof(Celula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
    Lista->Primeiro->Ant=NULL;
}

int Vazia(TipoLista Lista)
{
    return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(int x, TipoLista *Lista)
{
    Apontador Aux;
    Aux=Lista->Ultimo;
    Lista->Ultimo->Prox = (Apontador) malloc(sizeof(Celula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->chave = x;
    Lista->Ultimo->Prox = NULL;
    Lista->Ultimo->Ant=Aux;
    Lista->Ultimo->Indice=Lista->Ultimo->Ant->Indice+1;
}

void ImprimeListaNoArquivo(TipoLista Lista,FILE *fp)
{
    Apontador Aux;
    Aux = Lista.Primeiro->Prox;
    while (Aux != NULL)
    {
        fprintf(fp,"%d \n", Aux->chave);
        Aux = Aux->Prox;
    }
}

void EncheLista(TipoLista *Lista, int N, int semente){
    int i;
    Apontador Aux;
    Aux=Lista->Primeiro;
    srand(semente);
    for(i=0;i<N;i++){
        Insere(rand()%10000, Lista);
        Aux->Indice=i+1;
    }
}

void EncheVetor(int *Vetor, int N, int semente){
    int i;
    srand(semente);
    for(i=0;i<N;i++){
        *(Vetor + i)=rand()%10000;
    }
}

void quick_vetor(int *Vetor,int comeco, int fim, int *Contador){
    int pivot,aux,i,j;
    i=comeco;
    j=fim;
    pivot=mediana_vetor(Vetor,i,j);
    do{
        while (Vetor[i] < pivot){
            i++;
            Contador[0]=Contador[0]+1;
        } 
        while (Vetor[j] > pivot){
            j--;
            Contador[0]=Contador[0]+1;
        }
      
        if(i <= j){
            aux = Vetor[i];
            Vetor[i] = Vetor[j];
            Vetor[j] = aux;
            i++;
            j--;
            Contador[0]=Contador[0]+1;
            Contador[1]=Contador[1]+1;
        }
        Contador[0]=Contador[0]+1;
    }while(j > i);
   
    if(comeco < j){
        quick_vetor(Vetor, comeco, j,Contador);
        Contador[0]=Contador[0]+1;
    }
    if(i < fim){
        quick_vetor(Vetor, i, fim,Contador);
        Contador[0]=Contador[0]+1;
    }
}


void quick_lista(TipoLista *Lista, int comeco, int fim, Apontador Auxi, int *Contador){
    int pivot,Aux,i,j;
    Apontador Auxj;
    i=comeco;
    j=fim;
    while(Auxi->Indice!=i){
        Auxi=Auxi->Ant;
        Contador[0]=Contador[0]+1;
        Contador[1]=Contador[1]+1;
    }        
    Auxj=Auxi;
    Contador[1]=Contador[1]+1;
    while(Auxj->Indice<j){
        Auxj=Auxj->Prox;
        Contador[0]=Contador[0]+1;
        Contador[1]=Contador[1]+1;
    }
    pivot=mediana_lista(Lista,i,j,Auxi,Auxj);
    do{
        while(Auxi->chave<pivot){
            i++;
            Auxi=Auxi->Prox;
            Contador[0]=Contador[0]+1;
            Contador[1]=Contador[1]+1;
        }
        while(Auxj->chave>pivot){
            j--;
            Auxj=Auxj->Ant;
            Contador[0]=Contador[0]+1;
            Contador[1]=Contador[1]+1;
        }
        if(i<=j){
            Aux=Auxi->chave;
            Auxi->chave=Auxj->chave;
            Auxj->chave=Aux;
            i++;
            j--;
            Auxi=Auxi->Prox;
            Auxj=Auxj->Ant;
            Contador[0]=Contador[0]+1;
            Contador[1]=Contador[1]+5;
        }
        Contador[0]=Contador[0]+1;
    }while(j>i);
    if(comeco < j){
        quick_lista(Lista, comeco, j, Auxi, Contador);
        Contador[0]=Contador[0]+1;
    }
    if(i < fim){
        quick_lista(Lista, i, fim,Auxi, Contador);  
        Contador[0]=Contador[0]+1;
    }
}

int mediana_vetor(int *Vetor,int i,int j){    //função retorna o índice do elemento mediano
    int aux,a,b,c,d;
    d=(i+j)/2;
    a=*(Vetor+i);
    b=*(Vetor+d);
    c=*(Vetor+j);
    if(a>b && a>c){
        if(b>c){
            return b;
        }else{
            return c;
        }
    }
    else if(b>a && b>c){
        if(a>c){
            return a;
        }else{
            return c;
        }
    }
    else{
        if(b>a){
            return b;
        }else{
            return a;
        }
    }

}

int mediana_lista(TipoLista *Lista,int i, int j,Apontador Auxi, Apontador Auxj){
    Apontador Aux=Lista->Primeiro->Prox;
    int a,b,c,d=0;

    a=Auxi->chave;
    Aux=Lista->Primeiro->Prox;

    c=Auxj->chave;
    d=(i+j)/2;
    Aux=Lista->Primeiro->Prox;
    while(Aux->Indice!=d){
        Aux=Aux->Prox;
    }
    b=Aux->chave;
    if(a>b && a>c){
        if(b>c){
            return b;
        }else{
            return c;
        }
    }
    else if(b>a && b>c){
        if(a>c){
            return a;
        }else{
            return c;
        }
    }
    else{
        if(b>a){
            return b;
        }else{
            return a;
        }
    }
}


void ZeraLista(TipoLista *lista)
{
    if(Vazia(*lista))
    {
        printf("A lista ja esta vazia.\n");
    }
    else
    {
        Apontador aux1 = lista->Primeiro->Prox;
        Apontador aux2 = NULL;

        while(aux1 != NULL)
        {
            aux2 = aux1->Prox;
            free(aux1);
            aux1 = aux2;
        }

    lista->Ultimo = lista->Primeiro;
    lista->Primeiro->Prox = NULL;
    }
    

}
void DeletaLista(TipoLista *lista)
{
    if(lista->Primeiro == NULL)
    {
        printf("A lista nao existe!\n");
    }
    else
    {
        ZeraLista(lista);
        free(lista->Primeiro);
        lista->Primeiro = NULL;
        printf("Lista apagada!\n");
    }
    
}

void libera(TipoLista *Lista) //Desaloca os membros da lista
{
    if(!Vazia(*Lista)){
        Apontador proxNode;
        Apontador atual;
        
        atual = Lista->Primeiro->Prox;
        while(atual != NULL){           
            proxNode = atual->Prox; 
            free(atual);
            proxNode->Ant=NULL;
            atual = proxNode;
        }
    }
}

void LiberaLista(TipoLista *Lista, Apontador AuxLibera){
    if(AuxLibera->Prox!=NULL){
        AuxLibera=AuxLibera->Prox;
    }else{
        LiberaLista(Lista,AuxLibera);
    }
}

void ImprimeVetorNoArquivo(int *Vetor,FILE *fp, int N){
    int i;
    for(i=0;i<N;i++){
        fprintf(fp, "%d \n", Vetor[i]);
    }
}

