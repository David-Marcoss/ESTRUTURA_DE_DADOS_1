#include <stdio.h>
#include<stdlib.h>
#include<time.h>



typedef struct{
	int cod;
	char premios[60];
	int quant;
	
}premio;


typedef struct l{
	premio p;
	struct l *prox;
	struct l *ant;
	
}lista;


int num_aleatorio(){
	int num;

	num = rand() % 100;

	while(num == 0){
		num = rand() % 100;
	}


	return num;

}



void inicia(lista **inicio, lista **fim){
		*inicio = *fim = NULL;
}

void aloca(lista **No, premio p){
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

		(**No).ant = *inicio; 
		(**No).prox = *fim;
	
	}else if ( (**No).p.cod < (**inicio).p.cod){  // insere no inicio
		
		(**No).ant = *fim; 		    //faz o NO.ant apontar para o fim
		(**No).prox = *inicio; 	   //o NO. prox aponta para o inicio
		(**inicio).ant = *No; 	  // o inicio. ant aponta para o NO
		*inicio = *No;       	 // O inicio recebe o No
		(**fim).prox = *inicio; //  faz o fim.prox apontar para o novo inicio
	
	}else if ((**No).p.cod > (**fim).p.cod){  //insere no fim 
		
		(**fim).prox = *No;  //o fim.prox aponta para o NO
		(**No).ant = *fim; //O No.ant aponta para o fim

		(**No).prox = *inicio; //faz o novo fim apontar para o inicio

		*fim = *No; //fim recebe o No

		(**inicio).ant = *fim; //faz o inicio.ant apontar para novo fim
	
	
	}else{   // se o valor nao foi inserido no inicio nem no fim
		
		while((**No).p.cod > aux->p.cod){ // busca a posisao no qual vai ser inserido o valor
			
			aux= aux->prox;

		}
		if ((**No).p.cod != aux->p.cod){   
			
			(**No).ant = aux->ant; 

			(*(*aux).ant).prox = *No;
			aux->ant = *No;

			(**No).prox = aux;


		} // se nao entrar neste caso que dizer que o valor que o usuario quer inserir ja foi inserido
		 // e este valor é o que esta no inicio
	}

}
int remover(lista **inicio, lista **fim, int cod){ //remove um valor da lista
	int flag = 1;
	lista *aux, *auxiliar;
	
	aux = *inicio;

	if (*inicio != NULL){


		if (cod == (**inicio).p.cod && *inicio == *fim){ // se a lista tiver so um elemento
			
			*inicio = *fim = NULL;
			free(aux);

			flag = 0;
		

		}else if ( cod == (**inicio).p.cod){  // remove do inicio
			
			*inicio = (**inicio).prox;    //inicio aponta para o inicio.prox
			
			(**inicio).ant = *fim;  	 // e o inicio.ant apontar para o fim 
			(**fim).prox = *inicio;     // faz o fim.prox apontar para o novo inicio

			free(aux); 					// liebera o espaço alocado

			flag = 0;
			
		
		}else if (cod == (**fim).p.cod){  //remove do fim 
			
			aux = *fim;             //aux recebe o fim 
			*fim = (**fim).ant;    //fim recebe o fim.prox
			(**fim).prox = *inicio;  //fim.prox recebe inicio
			(**inicio).ant = *fim;

			free(aux);

			flag = 0;
		
		}else{   // se o valor nao foi inserido no inicio nem no fim
			
			while(cod > aux->p.cod && aux->prox != *inicio ){ // busca a posisao no qual vai ser inserido o valor
				
				aux= aux->prox;

			}
			if ( cod == aux->p.cod){   
				
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

	do{
		printf("\ncod: %d \n",aux->p.cod);
		printf("premio: %s \n",aux->p.premios);
		printf("qauntidade: %d \n",aux->p.quant);

		aux = aux->prox;
		
	}while(aux != inicio);

}


void busca(lista *inicio, lista *fim, int cod, lista **devolve){  //busca um valor  e devove uma estrutura com o valor
	lista *aux;
	int flag = 0;
	aux = inicio;


	if (inicio != NULL){
			
		if (cod < inicio->p.cod || cod > fim->p.cod){
			*devolve = NULL;
		
		}else{

			while(aux->prox != inicio  && cod > aux->p.cod){
				aux = aux->prox;
				
			}
			if (cod == aux->p.cod){
					*devolve = aux;
			
			}else{
				*devolve = NULL;
			}
		}
	
	}else{
		*devolve = NULL;
	}

}

void flush_in(){ 
	int ch;
	while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){} 
}


void insere_valores(lista **inicio, lista **fim){  //insere valores na lista
	lista *No,*aux;
	int flag;
	
	premio p;

	do{

		printf("digite o codigo: ");
		scanf("%d",&p.cod);

		busca(*inicio,*fim,p.cod,&aux);

		if (aux != NULL){
			printf("\nNao é possivel inserir premios com codigo repetido!!\n");
		
		}else{
			
			flush_in();  //LIMPA O BUFFER
			printf("premio: ");
			scanf("%[^\n]",p.premios);

			
			printf("qauntidade: ");
			scanf("%d",&p.quant);

			while(p.quant < 1){
				printf("qauntidade nao pode ser menor que 0\n digite quantidade valida: ");
				scanf("%d",&p.quant);

			}

			

			aloca(&No,p);

			insere(inicio,fim,&No);

		}
		getchar();
		
		printf("\ndigite -1 para sair 0 para continuar: ");
		scanf("%d",&flag);

	}while(flag!= -1);

}


void gira_roleta(lista **posisao, int flag){ //recebe uma posiçao da lista no primeiro caso
											// a posiçao é a do inicio da lista
	int num,i;                             // entao sorteia um valor e devove na variavel posição 
										  // a posição de onde parou na lista 
	srand(time(NULL));

	num = num_aleatorio();             //sorteia um valor

	//printf("\nroleta inicia na posisao: %s \n",(**posisao).p.premios);

	//printf("\nnumero sorteado: %d\n",num );
 
	for (i = 0; i < num-1; ++i){   //perrcorre a lista a quantidade de vezes do valor sorteado

		if (flag == 0){                    // se flag for 0
			*posisao = (**posisao).prox;  //gira a roleta no sentido horario
		
		}else{							  // se flag for 1
			*posisao = (**posisao).ant;  //gira a roleta no sentido ant-horario
		}
		
	}

	printf("\npremio sorteado: %s\n",(**posisao).p.premios);

	(**posisao).p.quant--;  // decrementa o premio que foi sorteado

}


void menu(int *op){ //imprime menu
	
	printf("\n1- Inserir premios na roleta\n");
	printf("2- Mostar premios \n");
	printf("3- Girar roleta\n");
	printf("4- sair \n");
	printf("\ndigite opcao: ");
	scanf("%d",op);
}


int main(){
	
	lista *inicio,*fim,*posisao; 
	
	int op=1,flag=0;
	
	inicia(&inicio,&fim);


	while(op!=4){
		
		menu(&op);

		switch(op){
			
			case 1:
					
				insere_valores(&inicio,&fim); //insere alunos na fila
				posisao = inicio;
					
				break;

			case 2:
				if (inicio != NULL){	 
					imprimir(inicio);
				}else{
					printf("\nFila vazia!!\n");
				}
				
				break;

			case 3:
				if (inicio != NULL){	           //a lista sempre é perrcoridada da posiçao onde ela parou na ultima vez
					gira_roleta(&posisao,flag);   //sorteia um premio

					if (posisao->p.quant == 0){                  //se a quantidade do premio sorteado for 0
						remover(&inicio,&fim,posisao->p.cod);   //remove o premio da lista
					}

					if (flag == 0){
						flag++;
					}else{
						flag--;
					}
				
				}else{
					printf("\nNao ha mais premios disponiveis!!\n");
				}

				
				break;

			case 4:
				printf("\nsaindo.....\n");
				break;

			
			default:
				printf("ERRO: opcao invalida \n");
				break;

		}
	}

	return 0;
}