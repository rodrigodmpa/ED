#include <stdio.h>
#include <stdlib.h>
#include "cenario2.h"
#include <sys/time.h>
#include <sys/resource.h>


void EncheVetor(int *Vetor, int N, int semente){
    int i;
    srand(semente);
    for(i=0;i<N;i++){
        *(Vetor + i)=rand()%10000;
    }
}


void quick_recursivo(int *Vetor,int comeco, int fim, int *Contador){
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
        quick_recursivo(Vetor, comeco, j,Contador);
        Contador[0]=Contador[0]+1;
    }
    if(i < fim){
        quick_recursivo(Vetor, i, fim,Contador);
        Contador[0]=Contador[0]+1;
    }
}

void quick_mediana_k(int *Vetor,int comeco, int fim, int *Contador,int k){
    int pivot,aux,i,j;
    i=comeco;
    j=fim;
    pivot=mediana_k(Vetor,i,j,k);
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
        quick_mediana_k(Vetor, comeco, j,Contador,k);
        Contador[0]=Contador[0]+1;
    }
    if(i < fim){
        quick_mediana_k(Vetor, i, fim,Contador,k);
        Contador[0]=Contador[0]+1;
    }
}

void quick_insertion(int *Vetor,int comeco, int fim, int *Contador, int m){
	int pivot,aux,i,j,c,atual,k;
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
		if((j-comeco <=m || (fim-i)<=m)){
			if(fim-i<=m)
			insertion_sort(Vetor,(fim-i),Contador);
			else
			insertion_sort(Vetor,(j-comeco),Contador);
		}

		if(comeco < j){
			quick_insertion(Vetor, comeco, j,Contador,m);
			Contador[0]=Contador[0]+1;
		}
		if(i < fim){
			quick_insertion(Vetor, i, fim,Contador,m);
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

int mediana_k(int *Vetor,int i,int j,int k){    //função retorna o índice do elemento mediano
    int *VetorAux,c,y,z,d=k/2,min,aux;
    VetorAux=(int *)malloc(k*sizeof(int));
    
    struct timeval semente;
    gettimeofday(&semente,NULL);
    srand((int)(semente.tv_sec + 1000000*semente.tv_usec));
    for(c=0;c<k;c++){
        y=(rand()%(j-i))+i;
        *(VetorAux+c)=Vetor[y];
    }   
    for (c = 0; c <= (k/2); c++) {
        min = c;
        for (z = (c+1); z < k; z++) {
            if(*(VetorAux+z) <  *(VetorAux+min)) min = z;
        }
            if (c != min) {
                aux = *(VetorAux+c);
                *(VetorAux+c) = *(VetorAux+min);
                *(VetorAux+min) = aux;
            }
    }
    aux=*(VetorAux+d);
    free(VetorAux);
    return aux;
}


void insertion_sort(int *Vetor, int tamanho, int *Contador) {
      int i, j, tmp;
      for (i = 1; i < tamanho; i++) {
            j = i;
            while (j > 0 && Vetor[j - 1] > Vetor[j]) {
                  tmp = Vetor[j];
                  Vetor[j] = Vetor[j - 1];
                  Vetor[j - 1] = tmp;
                  j--;
                  Contador[0] = Contador[0]+1;
                  Contador[1] = Contador[1]+1;
            }
      }
}

void ImprimeVetorNoArquivo(int *Vetor,FILE *fp, int N){
    int i;
    for(i=0;i<N;i++){
        fprintf(fp, "%d \n", Vetor[i]);
    }
}

