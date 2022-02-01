#include <stdio.h>
#include<stdlib.h>


typedef struct l{
	int valor;
	struct l *prox;
	
}lista;

void inicia(lista **inicio, lista **fim){
		*inicio = *fim = NULL;
}

void aloca(lista **No, int valor){
	lista *novo;

	novo = (lista*)malloc(sizeof(lista));
	novo->valor = valor;
	novo->prox = NULL;

	*No = novo;

}

void insere(lista **inicio, lista **fim, lista **No){
	lista *ant,*aux;
	
	ant = NULL;
	aux = *inicio;

	if (*inicio == NULL){       //primeiro caso
		*inicio = *fim = *No;
	
	}else if ( (**No).valor < (**inicio).valor){  // insere no inicio
		(**No).prox = *inicio;
		*inicio = *No;
		
	}else if ((**No).valor > (**fim).valor){  //insere no fim 
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

		} // se nao entrar neste caso que dizer que o valor que o usuario quer inserir ja foi inserido
		 // e este valor é o que esta no inicio
	}

}

void imprimir(lista *inicio){ //imprime a lista
	lista *aux;
	
	aux = inicio;

	while(aux != NULL){
		printf(" %d \n",aux->valor);
		aux = aux->prox;
		
	}

}
 
void insere_valores(lista **inicio, lista **fim){  //insere valores na lista
	lista *No;
	int n;

	do{
		printf("digite um valor: ");
		scanf("%d",&n);

		aloca(&No,n);

		insere(inicio,fim,&No);



	}while(n != 0);

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

int remover(lista **inicio, lista **fim, int valor){ //remove um valor da lista
	int flag = 0;

	lista *ant,*aux;
	
	ant = NULL;
	aux = *inicio;

	if(*inicio != NULL){  // se o inicio nao for nulo

		if (valor == (**inicio).valor && *inicio == *fim){ // se a lista tiver so um elemento
			
			*inicio = *fim = NULL;
			free(aux);

			flag = 1;
		

		}

		else if ((**inicio).valor == valor){ // remove o valor se o valor tiver no inicio da fila
			*inicio = (**inicio).prox;  // e muda o inicio da fila
			flag = 1;
			free(aux);
		
		}else{ // se o valor não estiver no inicio

			while(aux != NULL && valor > aux-> valor){ // percorre a lista buscando a posisao do valor que vai ser removido da lista
				ant = aux;
				aux = aux->prox;
			}
			
			if (valor == aux->valor){  // se a posição encontrada anteriormente for a posição do valor
				                      // que queremos remover
				if(aux == *fim){      //entao se o valor estiver no fim remove o valor e muda o fim da lista
					ant->prox = NULL;  
					*fim = ant;
					free(aux);
				
				}else{  // se o valor tiver entre o inicio e o fim da lista
					ant->prox = aux->prox;		//apenas remove o valor
					free(aux);

				}
				flag = 1;
			}

		}

	}


	return flag; //flag indica se o valor foi removido da lista 
				// fag == 1 o valor foi removido flag==0 o valor nao existe na lista
}


void menu(int *op){ //imprime menu
	
	printf("\n1- Inserir dados lista\n");
	printf("2- imprimir dados da lista \n");
	printf("3- busca valor \n");
	printf("4- remover valor \n");
	printf("5- sair \n");
	printf("\ndigite opcao: ");
	scanf("%d",op);
}


int main(){
	
	lista *inicio,*fim,*No, *aux; 
	int N,op=1;
	
	inicia(&inicio,&fim);

	while(op!=5){
		
		menu(&op);

		switch(op){
			
			case 1:
					
				insere_valores(&inicio,&fim); //insere alunos na fila
					
				break;

			case 2:	 
				imprimir(inicio);
				
				break;
			
			case 3:
				printf("digite o valor para busca: ");
				scanf("%d",&N);

				busca(inicio,fim,N,&aux);

				if (aux != NULL){
					printf("valor encontrado!\n");
					printf("valor: %d \n",aux->valor);
				}else{
					printf("valor nao encontrado!\n");
				}

				break;

			case 4:
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

			
			case 5:
				printf("\nsaindo.....\n");
				break;

			
			default:
				printf("ERRO: opcao invalida \n");
				break;

		}
	}

	return 0;
}