#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct F{   //declara a estrutura fila
	
	int valor;
	struct F *prox;

}Fila;

void aloca(Fila **No, int valor){  // aloca um estrutura do tipo fila

	*No = 	(Fila*) malloc( sizeof(Fila) );  //aloca estrutura
	(**No).valor = valor;                   // armazena o valor na estrutura alocada
	(**No).prox = NULL;                    // e faz o ponteiro prox apontar para null

}

void incia(Fila **Inicio, Fila **Fim){  //inicia um fila fazendo o inicio e o fim receber NUll
	 
	*Inicio = *Fim = NULL;

}

void enfilera(Fila **Inicio, Fila **Fim, Fila *No){ //enfileira um valor

	if (*Inicio == NULL){  		// se o inicio for nulo
		*Inicio = *Fim = No;  	// faz o inicio e o fim a pontar para a estrutura alocada
	
	}else{						// se nao for nulo
		(**Fim).prox = No;     // faz o fim.prox apontar para a estrutura alocada 
		*Fim = No;            // e faz o fim apontar para estrutura alocada

	}

}

int desenfilera(Fila **Inicio, Fila **Fim){   //retira um valor da fila sempre é retirado pelo inicio
	Fila *aux;
	int valor;

	if (*Inicio != NULL){     // se o inicio nao for nulo
		aux = *Inicio;        // faz o auxiliar receber o inicio
		valor = (**Inicio).valor;
		
		
		if ((**Inicio).prox != NULL){ //se o inicio.prox nao for nulo quer dizer que o ponteiro que ta na proxima posição nao é nulo
			*Inicio = (**Inicio).prox;  // entao faz o inicio apontar para o inicio.prox
		
		}else{ // se o inicio.prox  for nulo  quer dizer que esta na ultima posisao da fila
			*Inicio = *Fim = (**Inicio).prox;  // entao modifica o inicio e o fim faz conque eles sejam nulos

		}
		free(aux); //libera o espaçõ alocado

		return valor;	
	}

}

void insere(Fila **Inicio, Fila **Fim){
	Fila *No;
	int N,valor;

	do{
		printf("digite um valor: ");
		scanf("%d",&valor);

		aloca(&No,valor);

		enfilera(Inicio,Fim,No);



		//printf("digite 1 para continuar e 0 para parar: ");
		//scanf("%d",&N);


	}while(valor != -1 ); //enfileira valores enquanto o valor nao for negativo

}

void imprimir(Fila **Inicio, Fila **Fim){
	int valor;
	Fila *F_aux, *I_aux, *No; 			//cria um fila auxiliar

	incia(&I_aux,&F_aux); 				//inicia a fina auxiliar

	while(*Inicio != NULL){ 

		valor = desenfilera(Inicio,Fim); //desenfileira a fila de entrada e imprime o valor
		aloca(&No,valor);

		enfilera(&I_aux,&F_aux,No); 	// enfileira o valor reirado da fila de entrada


		printf("valor: %d\n",valor);

	}
	*Inicio = I_aux; 				//faz com que a fila de entrada receba a fila auxiliar
	*Fim = F_aux;

}

void menu(int *op){ //imprime menu
	
	printf("\n1- Inserir dados fila\n");
	printf("2- imprimir dados fila \n");
	printf("3- Sair \n");
	printf("\ndigite opcao: ");
	scanf("%d",op);
}



int main(){
	Fila *No;
	Fila *Inicio,*Fim;
	int valor,op=1;

	incia(&Inicio,&Fim);

	while(op!=3){
		
		menu(&op);

		switch(op){
			case 1:
					
				insere(&Inicio,&Fim);; //insere alunos na fila
					
				break;

			case 2:	 
				imprimir(&Inicio,&Fim);
				
				break;
			
			
			case 3:
				printf("\nsaindo.....\n");
				break;

			
			default:
				printf("ERRO: opcao invalida \n");
				break;

		}
	}


	return 0;
}

