#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "cenario1.h"


int main(int argc, char const *argv[])
{
    int *Vetor;
    int quantos_N,i,j,N,semente;
    TipoLista Lista;
    struct timeval inicio, final;
    int tmili,tmili2;
    FILE *fp1,*fp2,*fp3;
    int *Contador;

    if (argc != 4) //Caso seja inserido mais ou menos argumentos na linha de comando
    {
        printf("\nNúmero de argumentos inválido!\n ");
        return 1;
    }
    
    semente = atoi(argv[1]); // Pega a semente como parâmetro e a transforma em um inteiro
    fp1 = fopen(argv[2], "r"); //Abre o arquivo de entrada para leitura
    fp2 = fopen(argv[3], "w"); //Abre o arquivo de saida para gravação 

    if (fp1 == NULL || fp2 == NULL) //Caso o arquivo nao exista ou o nome esteja incorreto
    {
        printf("O arquivo '%s' nao pôde ser encontrado.\n", argv[2]); 
        return 1;
    }

    fscanf(fp1,"%d", &quantos_N); // Lê a quantidade de entradas (N's) que serão testadas

    Contador = (int *) malloc(2*sizeof(int)); // Aloca um vetor de tamanho 2 para guardar o número de comparações e de cópias

    for(i=0;i<quantos_N;i++) 
    {
        // Executa o quick_sorte em Vetor
        fscanf(fp1, "%d", &N);
        Vetor = (int *) malloc(N*sizeof(int));
        EncheVetor(Vetor,N,semente);
        fp3 = fopen("Ordenação/Vetores Desordenados.txt","a");
        fprintf(fp3,"\nVetor Desordenado com N = %d\n",N);
        ImprimeVetorNoArquivo(Vetor,fp3,N);
        gettimeofday(&inicio, NULL); //inicia a contagem do tempo de execução
        quick_vetor(Vetor,0,N,Contador);
        gettimeofday(&final, NULL); //termina a contagem do tempo de execução
        fp3 = fopen("Ordenação/Vetores Ordenados","a");
        fprintf(fp3,"\nVetor Desordenado com N = %d\n",N);
        ImprimeVetorNoArquivo(Vetor,fp3,N);
        tmili = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000); 
        fprintf(fp2,"Estatística para Vetores com Tamanho = %d:\n", N);
        fprintf (fp2,"Tempo de execução do sistema: %d milisegundos\n", tmili); //imprime no arquivo os tempos
        fprintf(fp2,"Número de comparação de chaves: %d\n",*(Contador+0));
        fprintf(fp2,"Número de cópias de registros: %d\n\n",*(Contador+1));
        *(Contador+0)=0;
        *(Contador+1)=0;

        // Executa o quick_sorte em Lista
        FLVazia(&Lista);
        EncheLista(&Lista, N, semente);
        fp3 = fopen("Ordenação/Listas Desordenadas.txt","a");
        fprintf(fp3,"\nLista Desordenada com N = %d\n",N);
        ImprimeListaNoArquivo(Lista,fp3);
        gettimeofday(&inicio, NULL); //inicia a contagem do tempo de execução
        quick_lista(&Lista, Lista.Primeiro->Prox->Indice, Lista.Ultimo->Indice, Lista.Primeiro->Prox, Contador);
        gettimeofday(&final, NULL); //termina a contagem do tempo de execução
        fp3 = fopen("Ordenação/Listas Ordenadas.txt","a");
        fprintf(fp3,"\nLista Ordenada com N = %d\n",N);
        ImprimeListaNoArquivo(Lista,fp3);
        tmili2 = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000);
        fprintf(fp2,"Estatística para Lista com Tamanho = %d:\n", N);
        fprintf (fp2,"Tempo de execução do sistema: %d milisegundos\n", tmili2); //imprime no arquivo os tempos
        fprintf(fp2,"Número de comparação de chaves: %d\n",*(Contador+0));
        fprintf(fp2,"Número de cópias de registros: %d\n\n",*(Contador+1));
        DeletaLista(&Lista);
        free(Vetor);
        *(Contador+0)=0;
        *(Contador+1)=0;

    }

    free(Contador);
    fclose(fp3);
    fclose(fp1);
    fclose(fp2);
    return 0;
}