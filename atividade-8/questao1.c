#include <stdio.h>
#include<stdlib.h>


typedef struct l{
	int valor;
	struct l *prox;
	struct l *ant;
	
}lista;

void inicia(lista **inicio, lista **fim){
		*inicio = *fim = NULL;
}

void aloca(lista **No, int valor){
	lista *novo;

	novo = (lista*)malloc(sizeof(lista));
	novo->valor = valor;
	novo->prox = novo->ant = NULL; //inicia anterior e prox com null

	*No = novo;

}

void insere(lista **inicio, lista **fim, lista **No){
	lista *aux;
	
	aux = *inicio;

	if (*inicio == NULL){       //primeiro caso
		*inicio = *fim = *No;
	
	}else if ( (**No).valor < (**inicio).valor){  // insere no inicio
		
		(**No).prox = *inicio; //o NO. prox aponta para o inicio
		(**inicio).ant = *No; // o inicio. ant aponta para o NO
		*inicio = *No;       // O inicio recebe o No
	
	}else if ((**No).valor > (**fim).valor){  //insere no fim 
		
		(**fim).prox = *No;  //o fim.prox aponta para o NO
		(**No).ant = *fim; //O No.ant aponta para o fim

		*fim = *No; //fim recebe o No
	
	
	}else{   // se o valor nao foi inserido no inicio nem no fim
		
		while((**No).valor > aux->valor){ // busca a posisao no qual vai ser inserido o valor
			
			aux= aux->prox;

		}
		if ((**No).valor != aux->valor){   
			
			(**No).ant = aux->ant; 

			(*(*aux).ant).prox = *No;
			aux->ant = *No;

			(**No).prox = aux;


		} // se nao entrar neste caso que dizer que o valor que o usuario quer inserir ja foi inserido
		 // e este valor é o que esta no inicio
	}

}
int remover(lista **inicio, lista **fim, int valor){ //remove um valor da lista
	int flag = 1;
	lista *aux, *auxiliar;
	
	aux = *inicio;

	if (*inicio != NULL){


		if (valor == (**inicio).valor && *inicio == *fim){ // se a lista tiver so um elemento
			
			*inicio = *fim = NULL;
			free(aux);

			flag = 0;
		

		}else if ( valor == (**inicio).valor){  // remove do inicio
			
			*inicio = (**inicio).prox;    //inicio aponta para o inicio.prox
			(**inicio).ant = NULL;  	 // e o inicio.ant recebe NUll
			free(aux); 					// liebera o espaço alocado

			flag = 0;
			
		
		}else if (valor == (**fim).valor){  //remove do fim 
			
			aux = *fim;             //aux recebe o fim 
			*fim = (**fim).ant;    //fim recebe o fim.prox
			(**fim).prox = NULL;  //fim.prox recebe NUll

			free(aux);

			flag = 0;
		
		}else{   // se o valor nao foi inserido no inicio nem no fim
			
			while(valor > aux->valor && aux != NULL){ // busca a posisao no qual vai ser inserido o valor
				
				aux= aux->prox;

			}
			if ( valor == aux->valor){   
				
				auxiliar = aux; 				  //auxiliar recebe a estrutura que iremos remover
				
				(*(*aux).prox).ant = aux->ant; 	 // O No que esta apos do valor que iremos remover
												// seu anterior ponta para o valor do aux.ant  que é o anterior de aux
				
				(*(*aux).ant).prox = aux->prox;  // O No que esta antes do valor que iremos remover
												// seu proximo ponta para o valor do aux.prox  que é o proximo de aux

				free(auxiliar); 
				
				flag = 0;


			} // se nao entrar neste caso que dizer que o valor que o usuario quer inserir ja foi inserido
			 // e este valor é o que esta no inicio
		}
	}

	return flag;	

}


void imprimir(lista *inicio){ //imprime a lista
	lista *aux;
	
	aux = inicio;

	while(aux != NULL){
		printf(" %d \n",aux->valor);
		aux = aux->prox;
		
	}

}

void imprimir_invertido(lista *fim){ //imprime a lista
	lista *aux;
	
	aux = fim;

	while(aux != NULL){
		printf(" %d \n",aux->valor);
		aux = aux->ant;
		
	}

}
void insere_valores(lista **inicio, lista **fim){  //insere valores na lista
	lista *No;
	int n;

	do{
		printf("digite -1 para sair: ");
		printf("digite um valor: ");
		scanf("%d",&n);

		if (n != -1){
			aloca(&No,n);
			insere(inicio,fim,&No);
		}



	}while(n != -1);

}

void busca(lista *inicio, lista *fim, int valor, lista **devolve){  //busca um valor  e devove uma estrutura com o valor
	lista *aux;
	int flag = 0;
	aux = inicio;


	if (inicio != NULL){
			
		if (valor < inicio->valor || valor > fim->valor){
			*devolve = NULL;
		
		}else{

			while(aux != NULL && valor > aux->valor){
				aux = aux->prox;
				
			}
			if (valor == aux->valor){
					*devolve = aux;
			
			}else{
				*devolve = NULL;
			}
		}
	
	}else{
		*devolve = NULL;
	}

}

int quant_vizinhos(lista *valor, int *cont){  //recebe um valor da lista e retorna pela função 
	int produto = 1;                               // o produto dos vizinhos do valor
 
	*cont = 0;                              // e retorna por parametro  quantos vizinhos o valor possui  

	if (valor->ant != NULL){

		(*cont)++;
		produto *= valor->ant->valor;


	}
	if (valor->prox != NULL){
		(*cont)++;
		
		produto *= valor->prox->valor;
	
	}

	return produto;

}


void menu(int *op){ //imprime menu
	
	printf("\n1- Inserir dados lista\n");
	printf("2- imprimir dados da lista \n");
	printf("3- imprimir lista invertida\n");
	printf("4- mostar qauntidade de vizinhos de um valor \n");
	printf("5- mostar prodruto entre os vizinhos de um valor \n");
	printf("6- remover valor \n");
	printf("7- sair \n");
	printf("\ndigite opcao: ");
	scanf("%d",op);
}


int main(){
	
	lista *inicio,*fim,*No, *aux; 
	int N,op=1,cont,produto;
	
	inicia(&inicio,&fim);

	while(op!=7){
		
		menu(&op);

		switch(op){
			
			case 1:
					
				insere_valores(&inicio,&fim); //insere alunos na fila
					
				break;

			case 2:
				if (inicio != NULL){	 
					imprimir(inicio);
				}else{
					printf("\nLista vazia!!\n");
				}
				
				break;

			case 3:	 
				
				if (inicio != NULL){	 
					imprimir_invertido(fim);
				}else{
					printf("\nLista vazia!!\n");
				}

				
				break;

			case 4:
				printf("digite o valor: ");
				scanf("%d",&N);

				busca(inicio,fim,N,&aux);

				if (aux != NULL){
					quant_vizinhos(aux,&cont);
					
					if (cont > 0){
						printf("\n%d possui: %d vizinhos\n",N,cont);
					}else{
						printf("\n%d nao possui vizinhos\n",N);
					}




				}else{
					printf("\nvalor nao encontrado!\n");
				}

				break;

			
			
			case 5:
				printf("digite o valor: ");
				scanf("%d",&N);

				busca(inicio,fim,N,&aux);

				if (aux != NULL){
					produto = quant_vizinhos(aux,&cont);
					
					printf("\nproduto dos vizinhos de %d: %d \n",N,produto);




				}else{
					printf("\nvalor nao encontrado!\n");
				}

				break;

			case 6:
				printf("digite o valor para remocao: ");
				scanf("%d",&N);

				busca(inicio,fim,N,&aux);

				if (aux != NULL){
					remover(&inicio,&fim,N);
					printf("\nvalor removido da lista!!\n");
				
				}else{
					printf("\nvalor nao encontrado!\n");
				}
				
					
				
				

				break;


			case 7:
				printf("\nsaindo.....\n");
				break;

			
			default:
				printf("ERRO: opcao invalida \n");
				break;

		}
	}

	return 0;
}