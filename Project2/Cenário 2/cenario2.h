#include <stdio.h>
#include <stdlib.h>

void EncheVetor(int *Vetor, int N, int semente);

void quick_recursivo(int vet[], int inicio, int fim,int *Contador);

int mediana_k(int *Vetor,int i,int j,int k);

void quick_mediana_k(int *Vetor,int comeco, int fim, int *Contador,int k);

void quick_insertion(int *Vetor,int comeco, int fim, int *Contador, int m);

void insertion_sort(int *Vetor, int tamanho, int *Contador);

int mediana_vetor(int *Vetor,int i,int j);

void ImprimeVetorNoArquivo(int *Vetor,FILE *fp, int N);