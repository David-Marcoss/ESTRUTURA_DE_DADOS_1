#include <stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
	char cpf[30];
	char nome[30];
	int idade;

}pessoa;


typedef struct l{
	pessoa p;
	struct l *prox;
	struct l *ant;
	
}lista;

void ler_pessoa(pessoa *p){

	printf("digite seu nome: ");
	scanf("%s",p->nome);
	
	printf("digite sua idade: ");
	scanf("%d",&p->idade);


}

void imprimir_pessoa(pessoa p){


	printf("\ncpf: %s\n",p.cpf);
	
	
	printf("nome: %s\n",p.nome);
	
	printf("idade: %d\n\n",p.idade);


}

void inicia(lista **inicio, lista **fim){
		*inicio = *fim = NULL;
}

void aloca(lista **No, pessoa p){
	lista *novo;

	novo = (lista*)malloc(sizeof(lista));
	novo->p = p;
	novo->prox = novo->ant = NULL; //inicia anterior e prox com null

	*No = novo;

}

void insere(lista **inicio, lista **fim, lista **No){
	lista *aux;
	
	aux = *inicio;

	if (*inicio == NULL){       //primeiro caso
		*inicio = *fim = *No;
	
	}else if (strcmp((**No).p.cpf , (**inicio).p.cpf ) < 0 ){  // insere no inicio
		
		(**No).prox = *inicio; //o NO. prox aponta para o inicio
		(**inicio).ant = *No; // o inicio. ant aponta para o NO
		*inicio = *No;       // O inicio recebe o No
	
	}else if (strcmp((**No).p.cpf , (**fim).p.cpf) > 0){  //insere no fim 
		
		(**fim).prox = *No;  //o fim.prox aponta para o NO
		(**No).ant = *fim; //O No.ant aponta para o fim

		*fim = *No; //fim recebe o No
	
	
	}else{   // se o valor nao foi inserido no inicio nem no fim
		
		while(strcmp((**No).p.cpf , aux->p.cpf) > 0){ // busca a posisao no qual vai ser inserido o valor
			
			aux= aux->prox;

		}
		if (strcmp((**No).p.cpf , aux->p.cpf) != 0){   
			
			(**No).ant = aux->ant; 

			(*(*aux).ant).prox = *No;
			aux->ant = *No;

			(**No).prox = aux;


		} // se nao entrar neste caso que dizer que o valor que o usuario quer inserir ja foi inserido
		 // e este valor é o que esta no inicio
	}

}
int remover(lista **inicio, lista **fim, char cpf[]){ //remove um valor da lista
	int flag = 1;
	lista *aux, *auxiliar;
	
	aux = *inicio;

	if (*inicio != NULL){


		if (strcmp((**inicio).p.cpf , cpf) == 0 && *inicio == *fim){ // se a lista tiver so um elemento

			*inicio = *fim = NULL;
			free(aux);

			flag = 0;
		

		}else if ( strcmp((**inicio).p.cpf , cpf) == 0){  // remove do inicio
			
			*inicio = (**inicio).prox;    //inicio aponta para o inicio.prox
			(**inicio).ant = NULL;  	 // e o inicio.ant recebe NUll
			free(aux); 					// liebera o espaço alocado

			flag = 0;
			
		
		}else if (strcmp((**fim).p.cpf , cpf) == 0){  //remove do fim 

		
			
			aux = *fim;             //aux recebe o fim 
			*fim = (**fim).ant;    //fim recebe o fim.prox
			(**fim).prox = NULL;  //fim.prox recebe NUll

			free(aux);

			flag = 0;
		
		}else{   // se o valor nao foi inserido no inicio nem no fim
			
			while(aux != NULL && strcmp(cpf , aux->p.cpf) > 0){ // busca a posisao no qual vai ser inserido o valor
				
				aux= aux->prox;

			}
			if (strcmp(cpf , aux->p.cpf) == 0){  
 
				
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

		imprimir_pessoa(aux->p);

		aux = aux->prox;
		
	}

}

void imprimir_invertido(lista *fim){ //imprime a lista
	lista *aux;
	
	aux = fim;

	while(aux != NULL){
		imprimir_pessoa(aux->p);
		aux = aux->ant;
		
	}

}


void busca(lista *inicio, lista *fim, char cpf[], lista **devolve){  //busca um valor  e devove  o ponteiro que aponta para o elemnto buscado se for encontrado
	lista *aux;														//e devolve null se nao encontrar
	int flag = 0;
	aux = inicio;


	if (inicio != NULL){

		if ( strcmp(cpf , inicio->p.cpf) < 0 || strcmp(cpf , fim->p.cpf) > 0){
			*devolve = NULL;
		
		}else{
			
			while(aux != NULL && strcmp(cpf , aux->p.cpf) > 0){
				aux = aux->prox;
					
			}
			if (strcmp(cpf , aux->p.cpf) == 0){
					*devolve = aux;
				
			}else{
				*devolve = NULL;
			}
		}
	
	}else{
		*devolve = NULL;
	}

}

void insere_valores(lista **inicio, lista **fim){  //insere valores na lista
	lista *No,*aux;
	int flag;
	
	pessoa p;

	do{

		printf("digite seu cpf: ");
		scanf("%s",p.cpf);

		busca(*inicio,*fim,p.cpf,&aux);

		if (aux != NULL){
			printf("\nNao é possivel inserir pessoa!!cpf invalido!!\n");
		
		}else{
			ler_pessoa(&p);

			aloca(&No,p);

			insere(inicio,fim,&No);

		}
	
		
		printf("\ndigite -1 para sair 0 para continuar: ");
		scanf("%d",&flag);

	}while(flag!= -1);

}

void lista_depois(lista **inicio, lista **fim, lista **I_l2,lista **F_l2 ,lista *aux){ //recebe a lita de entrada e devolve na lsta l2
	char cpf;                                                                         // uma lista contendo os valores que vem  depois do valor de aux
	
	pessoa auxiliar;                                                                 // aux aponta para os dados da pessoa digitada pelo usuario
	lista *No;


	aux = aux->prox; //aux aponta para o proximo


	while(aux != NULL){  //perrcore os valores que vem depois de aux
		                // e remove os valores da lista de entrada e insere na lista 2

		aloca(&No,aux->p); 

		insere(I_l2,F_l2,&No);

		remover(inicio,fim,aux->p.cpf);


		aux = aux->prox; //aux aponta para o proximo


	}



}

void lista_pessoas_idade(lista *inicio,lista *fim, lista **I_lidade, lista **F_lidade, int idade){ //devolve uma lista com as pessoa comidade abaixo da idade recebeida
	lista *aux,*No;
	

	if (inicio != NULL){

		aux = inicio;

		while(aux != NULL){

			if (aux->p.idade < idade){

				aloca(&No,aux->p);
				insere(I_lidade,F_lidade,&No);

			}

			aux = aux->prox;

		}
	}else{
		printf("\nNao é possivel realizar esta operação!! Lista vazia!!\n");
	}


}

void esvazia_lista(lista **inicio,lista **fim){ //remove todos elementos de uma lista
	lista *aux,*prox;

	aux = *inicio;

	while(aux != NULL){

		prox = aux->prox;

		remover(inicio,fim,aux->p.cpf);

		aux = prox;

	}

}

int vizinho_velho(lista *pessoa){ // recebe o ponteiro que aponta para uma pessoa da lista
	int idade;							  //e devolve a idade do vizinho mais velho	da pessoa	

	
	if (pessoa->ant == NULL && pessoa->prox == NULL){ // caso da pessoa nao ter vizinhos
		idade = -1;
	}

	else if(pessoa->ant == NULL){ //caso da pessoa esta na primeira posição da lista
		idade = pessoa->prox->p.idade;
	
	}else if (pessoa->prox == NULL){ //caso da pesso esta no fim da lista
		idade = pessoa->ant->p.idade;
	
	}else{  //caso em que ela esta no meio da lista

		if (pessoa->ant->p.idade > pessoa->prox->p.idade){
			idade = pessoa->ant->p.idade;
		
		}else{
			idade = pessoa->prox->p.idade;
		}

	}

	return idade;

}

void menu(int *op){ //imprime menu
	
	printf("\n1- Inserir dados lista\n");
	printf("2- imprimir dados da lista \n");
	printf("3- criar lista  contendo somente as pessoas  que estão depois de uma pessoa da lista ,\n");
	printf("4- mostrar lista comendo as pessoas menores do que uma idade informada\n");
	printf("5- mostrar a idade do vizinho mais velho de uma pessoa\n");
	printf("6- remover pessoa \n");
	printf("7- sair \n");
	printf("\ndigite opcao: ");
	scanf("%d",op);
}


int main(){
	
	lista *inicio,*fim,*No, *aux; 
	
	int N,op=1,idade;
	char cpf[30];

	pessoa auxiliar;

	lista *I_l2,*F_l2; // lista item A da questao
	lista *I_lidade, *F_lidade; //lita Item B da questao
	
	inicia(&inicio,&fim); //lista de entrada

	inicia(&I_l2,&F_l2);

	inicia(&I_lidade, &F_lidade);

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
				
				printf("digite o cpf: ");
				scanf("%s",cpf);

				busca(inicio,fim,cpf,&aux);

				if (I_l2 != NULL){
					esvazia_lista(&I_l2,&F_l2); // remove todos os elementos da lista se esta
												// operação ja tiver sido realizada
				
				}

				if (aux != NULL){
					
					if (aux->p.cpf == fim->p.cpf || inicio == fim){  //caso em que a pessoa estaja no fim da lista 
						                                            // ou a lista so tiver 1 elemento
						printf("\nNao é possivel realizar esta operacao!!\n");
					}else{
						lista_depois(&inicio,&fim,&I_l2,&F_l2,aux);  //gera uma nova lista

						printf("\nLista resultante: \n");
						imprimir(I_l2);
					}
					


				}else{
					printf("\npessoa nao encontrado!\n");
				}

				
				break;
			
			
			case 4:

				printf("digite a idade: ");
				scanf("%d",&N);

				if (I_lidade != NULL){
					esvazia_lista(&I_lidade,&F_lidade); // remove todos os elementos da lista se esta
												       // operação ja tiver sido realizada
				}

				lista_pessoas_idade( inicio,fim,&I_lidade,&F_lidade,N); //gera uma nova lista

				if (I_lidade != NULL){
					printf("\nLista de pessoas com a idade menor que a idade digitada: \n");
					imprimir(I_lidade);
				}else{
					printf("\nNao foi encontrado pessoas com idade menor do que a idade digitada!!\n");
				}

				

				break;


			case 5:
				printf("digite o cpf: ");
				scanf("%s",cpf);

				busca(inicio,fim,cpf,&aux);

				if (aux != NULL){
					
					idade = vizinho_velho(aux);

					if (idade < 0){
						printf("\npessoa nao possui vizinhos\n");
					
					}else{
						printf("\n idade do vizinho mais velho: %d \n", idade);

						if (aux->p.idade < idade){
							printf("o vizinho é mais velho do que a pessoa informada\n");
						
						}else{
							printf("o vizinho nao é mais velho do que a pessoa informada\n");
						}

					}

				
				}else{
					printf("\nvalor nao encontrado!\n");
				}
				
					
				
				

				break;


			case 6:
				printf("digite o valor para remocao: ");
				scanf("%s",cpf);

				busca(inicio,fim,cpf,&aux);

				if (aux != NULL){
					remover(&inicio,&fim,cpf);
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