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

	printf("\ndigite -1 para parar de inserir valores:\n");
	do{
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

	if (valor < inicio->valor || valor > fim->valor){ //se o valor for memor que o valor do inicio ou 
		*devolve = NULL;							 // ou valor for maior que o valor do fim quer dizer que o valor nao foi inserido na lista
	
	}else{ 

		while(aux != NULL && valor > aux->valor){ //busca o valor na lista
			aux = aux->prox;
			
		}
		if (valor == aux->valor){ //se o valor for encontrado 
				*devolve = aux;  // devolve um ponteiro com o valor buscado
		}else{
			*devolve = NULL;  //se o valor nao for encontrado devoleve null
		}
	}

}

int remover(lista **inicio, lista **fim, int valor){ //remove um valor da lista
	int flag = 0;

	lista *ant,*aux;
	
	ant = NULL;
	aux = *inicio;

	if(*inicio != NULL && (**inicio).valor <= valor && (**fim).valor >= valor){  // se o inicio nao for nulo e o valor e o valor nao for menor que o valor do 
																				// inicio nem maior que o valor do final , busca o elemento para remover
		
		if ((**inicio).valor == valor){ // remove o valor se o valor tiver no inicio da fila
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
	printf("2- Imprimir dados lista\n");
	printf("3- ver a soma dos elementos pares da lista\n");
	printf("4- ver  o  produto  dos  múltiplos  de  3  menores  do  que  60\n");
	printf("5- Remova um elemento da lista\n");
	printf("6- Altera um número\n");
	printf("7- sair \n");
	printf("\ndigite opcao: ");
	scanf("%d",op);
}

int soma_pares(lista *inicio){ //devolve a soma dos numeros pares da lista
								//calculo iterativo

	lista *aux;
	int somatorio=0;
	
	aux = inicio;

	while(aux != NULL){
		if (aux->valor % 2 == 0 ){
			somatorio+= aux->valor;
		}
		aux = aux->prox;
		
	}

	return somatorio;

}

void soma_pares_recursivo(lista *inicio, lista **aux, int *somatorio){ //devolve a soma dos numeros pares da lista
																		//calculo recursivo

	if(*aux != NULL){
		if ((*aux)->valor % 2 == 0 ){
			(*somatorio)+= (*aux)->valor;
		}
		*aux = (*aux)->prox;

		soma_pares_recursivo(inicio,aux,somatorio);
	}

	
}

int produto_multiplos(lista *inicio)	{//devolve o produto numeros da lista  for multiplo de 3 e menor 60
										//calculo iterarivo

	lista *aux;
	int produto=1;
	
	aux = inicio;

	while(aux != NULL){
		if ( ( aux->valor % 3 == 0 ) && (aux->valor < 60) && (aux->valor != 0)){
			produto*= aux->valor;
		}
		aux = aux->prox;
		
	}

	return produto;

}

void produto_multiplos_recursivo(lista *inicio, lista **aux, int *produto){ //devolve o produto numeros da lista  for multiplo de 3 e menor 60
																			//calculo recursivo

	if(*aux != NULL){ 
		
		if( (**aux).valor % 3 == 0 && (**aux).valor != 0 && (**aux).valor < 60 ){ // se o numero for multiplo de 3 e menor 60
			(*produto) *= (*aux)->valor;  //calcula o produto
		}
		
		*aux = (*aux)->prox; //passa para o proximo elemento da lista

		produto_multiplos_recursivo(inicio,aux,produto); //perrcorre a lista enquanto aux nao for nulo
	}

	
}


int main(){
	
	lista *inicio,*fim,*No, *aux; 
	int N,N2,soma,produto,op=1,flag;
	
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
					printf("\nERRO!! Lista vazia\n");
				}
				
				break;
			

			case 3:	 
				if (inicio != NULL){
					aux = inicio;
					soma = 0;
					soma_pares_recursivo(inicio,&aux,&soma); // calculo recursivo
					//soma = soma_pares(inicio);   	//calculo iterativo

					printf("\nsoma dos numeros pares da lista : %d\n",soma);
				
				}else{
					printf("\nERRO!! Lista vazia\n");
				}
				
				break;
			
			case 4:
				if (inicio != NULL){
					aux = inicio;
					produto = 1;
					produto_multiplos_recursivo(inicio,&aux,&produto); // calculo recursivo
					//soma = soma_pares(inicio);   	//calculo iterativo  //calculo iterativo

					printf("\nproduto: %d\n",produto);
				}else{
					printf("\nERRO!! Lista vazia\n");
				}
				
				
				break;

			case 5:
				if (inicio != NULL){
					printf("digite o valor: ");  //remove um valor da lista
					scanf("%d",&N);

					flag = remover(&inicio,&fim,N);

					if (flag == 1){
						printf("\nvalor removido da lista!!\n");
					
					}else{
						printf("\nERRO!! valor nao encontrado\n");

					}
				}else{
					printf("\nERRO!! Lista vazia\n");
				}

				break;

			
			case 6:

				if (inicio != NULL){
					
					printf("digite o valor que voce deseja altera: ");
					scanf("%d",&N);

					busca(inicio,fim,N,&aux);

					if (aux != NULL){
						printf("digite o novo valor para a alteracao: ");
						scanf("%d",&N2);

						flag = remover(&inicio,&fim,N);

						if(flag == 1){
							aloca(&No,N2);
							insere(&inicio,&fim,&No);

							printf("\nvalor alterado com sucesso!!\n");
						
						}

						
					
					}else{
						printf("\nvalor que voce deseja alterar nao existe na lista!\n");
					}

				}else{
					printf("\nERRO!! Lista vazia\n");
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