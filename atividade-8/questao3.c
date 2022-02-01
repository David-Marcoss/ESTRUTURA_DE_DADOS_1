#include <stdio.h>
#include<stdlib.h>
#include<time.h>


typedef struct l{
	int valor;
	int quant_escolhido;  //quantidade de vezes que o valor foi escolhido
	struct l *prox;
	
}lista;

int num_aleatorio(){

	return rand() % 500;

}

void inicia(lista **inicio, lista **fim){
		*inicio = *fim = NULL;
}

void aloca(lista **No, int valor){
	lista *novo;

	novo = (lista*)malloc(sizeof(lista));
	novo->valor = valor;
	novo->quant_escolhido = 0;
	novo->prox = NULL;

	*No = novo;

}

int insere(lista **inicio, lista **fim, lista **No){
	lista *ant,*aux;
	int flag = 1; //indica se o valor foi inserido
	
	ant = NULL;
	aux = *inicio;

	if (*inicio == NULL){       //primeiro caso
		
		*inicio = *fim = *No;
		(**No).prox = *inicio;    // faz o NO apontar para o Inicio

	
	}else if ( (**No).valor < (**inicio).valor){  // insere no inicio
		
		(**No).prox = *inicio;
		*inicio = *No;

		(**fim).prox = *inicio; //faz o fim.prox apaontar para o novo inicio

		
		
	}else if ((**No).valor > (**fim).valor){  //insere no fim 
		
		(**No).prox = *inicio; //faz o NO.prox apaontar para o inicio
		
		(**fim).prox = *No;
		*fim = *No;

		
	
	}else{   // se o valor nao foi inserido no inicio nem no fim
		
		while((**No).valor > aux->valor){ // busca a posisao no qual vai ser inserido o valor
			ant = aux;
			aux= aux->prox;

		}
		if ((**No).valor != aux->valor){   
			ant->prox = *No;     //inser o valor na posição correta
			(**No).prox = aux;


		}else{
			flag = 0;
		} 		// se entrar neste caso que dizer que o valor que o usuario quer inserir ja foi inserido
		 	
	}

	return flag;

}

void imprimir(lista *inicio){ //imprime a lista
	lista *aux;
	
	aux = inicio;

	do{
		printf(" %d \n",aux->valor);
		aux = aux->prox;
		
	}while(aux != inicio);

}
 
void insere_valores(lista **inicio, lista **fim){  //insere valores na lista
	lista *No;
	int n,flag,quant_valores=0;

	srand(time(NULL));

	do{	

		n = num_aleatorio();
		
		if (n != 0){
			aloca(&No,n);

			flag = insere(inicio,fim,&No);

		}

		if (flag == 1){
			quant_valores++;

		}



	}while(quant_valores != 100);


}

void busca(lista *inicio, lista *fim, int valor){  //busca um valor  e mostra o valor se encontrar e mostra os valore aproximados se nao encontrar
	lista *aux,*ant;
	int flag = 0;
	aux = inicio;

	if (valor < inicio->valor){
		printf("\nvalor nao encontrado:\n");
		printf("valores aproximados :  %d e %d \n", inicio->valor , inicio->prox->valor);
		
	}else{

		while(aux->prox != inicio && valor > aux->valor){
			ant = aux;
			aux = aux->prox;
					
		}
		if (valor == aux->valor){
				printf("\nvalor encontrado \n");
				aux->quant_escolhido++;
				printf("quantidade vezes escolhido: %d \n", aux->quant_escolhido);
				
		}else{
			printf("\nvalor nao encontrado:\n");
			printf("valores aproximados :  %d e %d \n", ant->valor , aux->valor );
		}
	}
	

}

void roda(lista *inicio){   // gera um valor e roda a lista a quntidade de vezes do valor
	lista *aux;            // entao mostra o valor que parou e a quantidade de voltas na lista 
	int num,i,voltas = 0;

	num = num_aleatorio();

	printf("\nnumero sorteado: %d\n",num);

	aux = inicio;

	for (i = 0; i < num; ++i){
		printf("roda peao: %d\n",aux->valor );
		aux = aux->prox;

		if (aux == inicio){
			voltas++;
		}
	}	

	printf("\nvalor parou em : %d\n",aux->valor);
	printf("quantidade de voltas: %d\n", voltas);

}


void menu(int *op){ //imprime menu
	
	printf("\n1- lançar uma ficha\n");
	printf("2- sair \n");
	printf("\ndigite opcao: ");
	scanf("%d",op);
}


int main(){
	
	lista *inicio,*fim,*No, *aux; 
	int N,op=1;
	
	inicia(&inicio,&fim);

	insere_valores(&inicio,&fim); //insere alunos na fila

	printf("\nlista de valores criada: \n");

	while(op!=2){
		
		menu(&op);

		switch(op){
			
			case 1:
				printf("digite o valor entre 1 e 500: ");
				scanf("%d",&N);

				while(N<1 || N> 500){
					printf("digite o valor valido entre 1 e 500: ");
					scanf("%d",&N);

				}

				/*N = num_aleatorio();
				printf("\nficha lancada: %d\n",N);*/ // valor gerado alearorio

				busca(inicio,fim,N);

					
				break;

			case 2:
				printf("\nsaindo.....\n");
				break;

			
			default:
				printf("ERRO: opcao invalida \n");
				break;

		}
	}

	//imprimir(inicio);

	//roda(inicio);

	return 0;
}