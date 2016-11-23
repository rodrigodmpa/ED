#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "funcoes.h"
#include <math.h>

int main(int argc, char *argv[])
{
    int elevador_com_pessoa = 0;
    int i, iteracao, Npessoas, Nandares;
    int andar_atual = 0, andar_destino, tempo_decorrido, tempo_dentro;
    int hora_chamada, andar_inicial;
    int variavel; //variavel apenas utilizada para "contar" quantas pessoas tem no arquivo
    node *pessoas, *vetor;
    struct timeval aleatorio, tempo_u, tempo_s;
    struct rusage usage;
    FILE *fp;

    getrusage(RUSAGE_SELF, &usage); //inicia a contagem do tempo de execucao

    if (argc > 2 || argc == 1) 
    {
        if (argc > 2) //Caso sejam passados mais de 2 argumentos no terminal
        {
            printf("Numero de argumentos invalido\n");
            return 1;
        }
        printf("Os argumentos devem seguir o modelo \"elevador.exe\" \"nomedotxt.txt\" \n");
    }
    else if (argc == 2)
    {
        fp = fopen(argv[1], "r+"); //Abre o arquivo para leitura
        if (fp == NULL)
        {
            printf("O arquivo nao pode ser encontrado\n"); //Caso o arquivo nao exista ou o nome esteja incorreto
            return 1;
        }
    }

    if (argv[1] == NULL) //Caso o usuario execute o programas mas nao digite o segundo argumento (nome do txt)
    {
        printf("Criando .txt com o nome \"rotina.txt\"\n");
        fp = fopen("rotina.txt", "w+"); //Cria um txt com o nome de rotina.txt
        printf("Digite o numero de pessoas\n");
        scanf("%d", &Npessoas);
        vetor = (node *) malloc (Npessoas*sizeof(node)); //Aloca um vetor do tipo node para armazenar uma pessoa e seus dados
        printf("Digite o numero de andares\n");
        scanf("%d", &Nandares);
        gettimeofday(&aleatorio, NULL); //Pega a hora do dia
        srand(aleatorio.tv_sec); //Usa os segundos para fazer um numero aleatorio

        for(i = 0; i < Npessoas; i++) //Gera os dados no .txt com valores aleatorios e coerentes
        {   
            fprintf(fp,"%d ", i+1);
            hora_chamada = rand()%20;
            fprintf(fp,"%d ", hora_chamada);
            andar_inicial = rand()%Nandares;
            fprintf(fp,"%d ", andar_inicial);
            andar_destino = rand()%Nandares;

            while (andar_destino == andar_inicial) //Arruma caso o andar de destino seja o mesmo que o inicial
            {
                andar_destino = rand()%Nandares;           
            }
        fprintf(fp,"%d", andar_destino);
        fprintf(fp,"\n");
        }
    }

    if (argc == 2) 
    {
        Npessoas = 0;
        for(i=0 ; !feof(fp); i++) //Se forem recebidos 2 argumentos, o numero de pessoas eh contado
        {
            fscanf(fp, "%d", &variavel); //"variavel" conta quantas pessoas tem no arquivo 
            fscanf(fp, "%d", &variavel);
            fscanf(fp, "%d", &variavel);
            fscanf(fp, "%d", &variavel);
            Npessoas++;
        }
        vetor = (node *) malloc (Npessoas*sizeof(node)); //Aloca um vetor do tipo node para armazenar uma pessoa e seus dados
    }

    rewind(fp); //"Rebobina" o arquivo para colocar os dados no vetor

    for(i=0 ; i < Npessoas; i++) //Coloca cada dado de cada pessoa no vetor
    {
        fscanf(fp,"%d", &vetor[i].id);
        fscanf(fp,"%d", &vetor[i].hora_chamada);
        fscanf(fp,"%d", &vetor[i].andar_inicial);
        fscanf(fp,"%d", &vetor[i].andar_destino);
    }

    bubblesort (vetor, Npessoas); //Organiza por ordem crescente do tempo em que as pessoas chamam o elevador
    pessoas = (node *) malloc(sizeof(node)); //Aloca o espaco de uma pessoa para permitir a inicializacao
    inicia(pessoas); //Inicia a lista

    for(i=0;i<Npessoas;i++)
    {
        insereFim_vetor(pessoas, vetor[i]); //Transfere as pessoas do vetor para a lista, ja ordenado por hora de chamada do elevador
    }
    
    imprime_lista (pessoas, Npessoas); //Mostra os dados das pessoas na lista

    free(vetor); //Desaloca o vetor ja sua unica funcao era ordenar os dados por hora de chamada do elevador

    printf ("O elevador esta no %d andar\n", andar_atual); 

    iteracao = 1;
    node *aux; //Usada para manipular a lista sem que haja perda de cada elemento

    for(aux = pessoas; aux != NULL; aux=aux->prox) //Eh executado ate que todos as pessoas cheguem ao destino
    {
        tempo_dentro = fabs(aux->andar_inicial - aux->andar_destino); //O tempo dentro do elevador sempre sera a diferenca entre o andar inicial e o andar destino
        if (iteracao == 1) //Iguala o tempo decorrido caso a primeira pessoa chame o elevador num tempo diferente de 0
        {
            tempo_decorrido = aux->hora_chamada;
        }

        andar_destino = aux->andar_inicial; //iguala o destino do elevador com o andar aonde a pessoa esta

        while (andar_atual != andar_destino) //inicia o movimento do elevador 
        {
            if (andar_atual < andar_destino)
            {
                while (andar_atual < andar_destino) //caso elevador tenha que subir
                {	
                	checatempo(aux,tempo_decorrido);
                    andar_atual++; //"caminha" para cada andar
                    tempo_decorrido++; //Incrementa o tempo zepslon
                    printf ("O elevador esta no %do andar\n", andar_atual);
                    //sleep (1); //espera 1s para andar              
                }
            }
            else 
            {
                while (andar_atual > andar_destino) //caso elevador tenha que descer
                {	
                	checatempo(aux,tempo_decorrido);
                    andar_atual--; //"caminha" para cada andar
                    tempo_decorrido++; //Incrementa o tempo zepslon
                    printf ("O elevador esta no %do andar\n", andar_atual);
                    //sleep (1); //espera 1s para andar
                }
            }
                    
            if (!elevador_com_pessoa) //Quando o elevador chega ao destino ele "pega a pessoa"
            {
                printf ("O elevador chegou no %do andar e pegou a pessoa %d\n", andar_atual, aux->id);
                elevador_com_pessoa = 1;
                checatempo(aux,tempo_decorrido);
                tempo_decorrido++; //Quando uma ou mais pessoas entram no elevador
                andar_destino = aux->andar_destino; //O novo destino passa a ser o destino da pessoa dentro do elevador                
            }
            
            if (aux->andar_destino == andar_atual && elevador_com_pessoa) 
            {
                printf ("O elevador chegou no %do andar e deixou a pessoa %d\n", andar_atual, aux->id);
                printf ("\n----------------\n");
                printf ("Estatisticas para a pessoa %d:\n", aux->id);
                printf("Hora do dia(tempo total decorrido): %d\nHora chamada: %d\nTempo de espera: %d zepslons\n", tempo_decorrido, aux->hora_chamada, aux->wait_time);
                printf("Tempo dentro do elevador: %d zepslons\n", tempo_dentro);
                printf ("----------------\n\n");
                checatempo(aux,tempo_decorrido);
                tempo_decorrido++; //Quando uma ou mais pessoas saem do elevador
                elevador_com_pessoa = 0; //Esvazia o elvador quando a pessoa chega ao seu destino
            }       
            iteracao++; //incrementa a iteracao
        }
    }

    fclose(fp);
    libera(pessoas);
    free(pessoas);
    free(aux);
    getrusage(RUSAGE_SELF, &usage); //pega a contagem a partir do incio do tempo de execucao
    tempo_s = usage.ru_stime; //pega o tempo de excucao em modo usuario
    tempo_u = usage.ru_utime; //pega o tempo de excucao em modo kernel
    printf ("Tempo de execucao do sistema: %ld.%.6lds\n", tempo_s.tv_sec, tempo_s.tv_usec); //imprime na tela os tempos
    printf ("Tempo de execucao do usuario: %ld.%.6lds\n", tempo_u.tv_sec, tempo_u.tv_usec);

    return 0;
}
