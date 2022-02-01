#include<stdio.h>
#include<stdlib.h>

typedef struct _Pilha{
	int valor;
	struct _Pilha *ant;

}Pilha;


void aloca(Pilha **No){
      Pilha *novo;      //cria uma strutura do tipo pilha

      novo = NULL;

      novo = (Pilha*)malloc(sizeof(Pilha));  //aloca essa estrutura

      *No = novo; //e faz o no receber a estrutura alocada

}

void empilha(int valor,Pilha **topo, Pilha *No){
	
	if (No != NULL){  			//se o no for diferente de NULL quer dizer que o valor foi alocado corretamente
		(*No).valor = valor;   // faz o no receber o valor
		(*No).ant = *topo;    //  e o no anterior recebe o topo
		*topo = No;          // o topo recebe o conteudo do no


	}

}

int desempilha(Pilha **topo){
	int valor;
	Pilha *aux;

	if(*topo != NULL){	 			// se o topo nao for nulo
		valor = (**topo).valor; 	// o valor recebe o conteudo que ta no topo
		aux = *topo;                // auxiliar aopmnta pro topo
		*topo = (**topo).ant;      // o topo a ponta para o valor que ta na posição anterior

		free(aux);             // e da um free no topo

		
	}

	return valor;
}

void insere(Pilha **topo){
	Pilha *No;
	int N;

	do{
		 aloca(&No);
	     empilha(N,topo,No);
		 printf("digite o valor: ");
		 scanf("%d",&N);
	
	}while (N != 0);	

}

void retirar(Pilha **topo){
 	int n;
	
	while (*topo !=NULL){
	     n = desempilha(topo);

	     printf("%d\n",n);

	}	

}


int main(){
	Pilha *topo;

	topo = NULL;

	insere(&topo);
	retirar(&topo);

	return 0;
}