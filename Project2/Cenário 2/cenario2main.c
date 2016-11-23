#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "cenario2.h"

int main(int argc, char *argv[])
{
	int *Vetor;
    int quantos_N,i,N,semente;
    struct timeval inicio, final;
    int tmili,tmili2;
    int k,m;
    FILE *fp1,*fp2,*fp3;
    int *Contador;
	if (argc != 6) //Caso seja inserido mais ou menos argumentos na linha de comando
    {
        printf("\nNúmero de argumentos inválido!\n ");
        return 1;
    }

    semente = atoi(argv[1]);
    k = atoi(argv[4]);
    m = atoi(argv[5]);

    fp1 = fopen(argv[2], "r"); //Abre o arquivo de entrada para leitura
    fp2 = fopen(argv[3], "w"); //Abre o arquivo de saida para gravação

    if (fp1 == NULL || fp2 == NULL) //Caso o arquivo nao exista ou o nome esteja incorreto
    {
        printf("O arquivo '%s' não pôde ser encontrado.\n", argv[2]); 
        return 1;
    }

    fscanf(fp1,"%d", &quantos_N); // Lê a quantidade de entradas (N's) que serão testadas

    Contador = (int *) malloc(2*sizeof(int)); // Aloca um vetor de tamanho 2 para guardar o número de comparações e de cópias

    for(i=0;i<quantos_N;i++) 
    {
        // Executa o quick_sort Recursivo
        fscanf(fp1, "%d", &N);
        Vetor = (int *) malloc(N*sizeof(int));
        EncheVetor(Vetor,N,semente);
        fp3 = fopen("Ordenação/Vetores Desordenados no Quick Recursivo.txt","a");
        fprintf(fp3,"\nVetor Desordenado com N = %d\n",N);
        ImprimeVetorNoArquivo(Vetor,fp3,N);
        gettimeofday(&inicio, NULL); //inicia a contagem do tempo de execução
        quick_recursivo(Vetor,0,N,Contador);
        gettimeofday(&final, NULL); //termina a contagem do tempo de execução
        fp3 = fopen("Ordenação/Vetores Ordenados pelo Quick Recursivo.txt","a");
        fprintf(fp3,"\nVetor Ordenado com N = %d\n",N);
        ImprimeVetorNoArquivo(Vetor,fp3,N);
        tmili = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000); 
        fprintf(fp2,"Estatística do quick_recursivo para Vetores com Tamanho = %d:\n", N);
        fprintf (fp2,"Tempo de execução do sistema: %d milisegundos\n", tmili); //imprime no arquivo os tempos
        fprintf(fp2,"Número de comparação de chaves: %d\n",*(Contador+0));
        fprintf(fp2,"Número de cópias de registros: %d\n\n",*(Contador+1));
        *(Contador+0)=0;
        *(Contador+1)=0;
        free(Vetor);

        // Executa o quick_sort mediana(k)
        Vetor = (int *) malloc(N*sizeof(int));
        EncheVetor(Vetor,N,semente);
        fp3 = fopen("Ordenação/Vetores Desordenados no Quick Mediana(k).txt","a");
        fprintf(fp3,"\nVetor Desordenado com N = %d\n",N);
        ImprimeVetorNoArquivo(Vetor,fp3,N);
        gettimeofday(&inicio, NULL); //inicia a contagem do tempo de execução
        quick_mediana_k(Vetor,0,N,Contador,k);
        gettimeofday(&final, NULL); //termina a contagem do tempo de execução
        fp3 = fopen("Ordenação/Vetores Ordenados pelo Quick Mediana(k).txt","a");
        fprintf(fp3,"\nVetor Ordenado com N = %d\n",N);
        ImprimeVetorNoArquivo(Vetor,fp3,N);
        tmili = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000); 
        fprintf(fp2,"Estatística do quick_mediana_k com k = %d para Vetores com Tamanho = %d:\n",k, N);
        fprintf (fp2,"Tempo de execução do sistema: %d milisegundos\n", tmili); //imprime no arquivo os tempos
        fprintf(fp2,"Número de comparação de chaves: %d\n",*(Contador+0));
        fprintf(fp2,"Número de cópias de registros: %d\n\n",*(Contador+1));
        *(Contador+0)=0;
        *(Contador+1)=0;
        free(Vetor);

        // Executa o quick_sorte Inserção(m)
        Vetor = (int *) malloc(N*sizeof(int));
        EncheVetor(Vetor,N,semente);
        fp3 = fopen("Ordenação/Vetores Desordenados no Quick Inserção(m).txt","a");
        fprintf(fp3,"\nVetor Desordenado com N = %d\n",N);
        ImprimeVetorNoArquivo(Vetor,fp3,N);
        gettimeofday(&inicio, NULL); //inicia a contagem do tempo de execução
        quick_insertion(Vetor,0,N,Contador,m);
        gettimeofday(&final, NULL); //termina a contagem do tempo de execução
        fp3 = fopen("Ordenação/Vetores Ordenados pelo Quick Inserção(m).txt","a");
        fprintf(fp3,"\nVetor Ordenado com N = %d\n",N);
        ImprimeVetorNoArquivo(Vetor,fp3,N);
        tmili = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000); 
        fprintf(fp2,"Estatística do quick_insertion com m = %d para Vetores com Tamanho = %d:\n",m, N);
        fprintf (fp2,"Tempo de execução do sistema: %d milisegundos\n", tmili); //imprime no arquivo os tempos
        fprintf(fp2,"Número de comparação de chaves: %d\n",*(Contador+0));
        fprintf(fp2,"Número de cópias de registros: %d\n\n",*(Contador+1));
        *(Contador+0)=0;
        *(Contador+1)=0;
        free(Vetor);    
    }

	free(Contador);
    fclose(fp1);
    fclose(fp2);


	return 0;
}