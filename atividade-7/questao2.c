#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct l{
	char str[30];
	struct l *prox;
	
}lista;

typedef struct { //recebe as strings vizinhas
	char ant[30];
	char prox[30];
}vizinhas;

void inicia(lista **inicio, lista **fim){
		*inicio = *fim = NULL;
}

void aloca(lista **No, char *str){ //aloca no e insere string no NO
	lista *novo;

	novo = (lista*)malloc(sizeof(lista));
	strcpy(novo->str, str);
	novo->prox = NULL;

	*No = novo;

}

void insere(lista **inicio, lista **fim, lista **No){ //insere oredenado por oredenado alfabetica
	lista *ant,*aux;
	
	ant = NULL;
	aux = *inicio;

	if (*inicio == NULL){       //primeiro caso
		*inicio = *fim = *No;
	
	}else if ( strcmp((**No).str , (**inicio).str ) < 0  ){  //se a sritring que queremos inserir for menor que a srtring do inicio
		(**No).prox = *inicio;							// insere a string no inicio e muda o inicio
		*inicio = *No;
		
	}else if ( strcmp((**No).str , (**fim).str) > 0){  //se a sritring que queremos inserir for maior que a srtring do fim
		(**fim).prox = *No;                           // insere a string no fim e muda o fim
		*fim = *No;
	
	}else{   // se o valor nao foi inserido no inicio nem no fim
		
		while( strcmp((**No).str , aux->str) > 0){ // busca a posisao no qual vai ser inserido o valor
			ant = aux;
			aux= aux->prox;

		}
		if (strcmp((**No).str , aux->str) != 0) {   // se as strings nao forem igauis
			ant->prox = *No;     //inser o valor na posição correta
			(**No).prox = aux;

		} // se nao entrar neste caso que dizer que o valor que o usuario quer inserir ja foi inserido
		 
	}

}

void insere_por_tam(lista **inicio, lista **fim, lista **No){ //insere oredenando por tamanho
	lista *ant,*aux;
	
	ant = NULL;
	aux = *inicio;

	if (*inicio == NULL){       //primeiro caso
		*inicio = *fim = *No;
	
	}else if ( strlen((**No).str) <= strlen((**inicio).str)  ){  //se a sritring que queremos inserir for menor que a srtring do inicio
		(**No).prox = *inicio;							// insere a string no inicio e muda o inicio
		*inicio = *No;
		
	}else if ( strlen((**No).str) >= strlen((**fim).str)){  //se a sritring que queremos inserir for maior que a srtring do fim
		(**fim).prox = *No;                           // insere a string no fim e muda o fim
		*fim = *No;
	
	}else{   // se o valor nao foi inserido no inicio nem no fim
		
		while( strlen((**No).str) >= strlen(aux->str)){ // busca a posisao no qual vai ser inserido o valor
			ant = aux;
			aux= aux->prox;

		}
		if(strcmp((**No).str , aux->str) != 0){   // se as strings nao forem igauis
			ant->prox = *No;     //inser o valor na posição correta
			(**No).prox = aux;

		} // se nao entrar neste caso que dizer que o valor que o usuario quer inserir ja foi inserido
		 
	}

}

void imprimir(lista *inicio){ //imprime a lista
	lista *aux;
	
	aux = inicio;

	while(aux != NULL){
		printf(" %s \n",aux->str);
		aux = aux->prox;
		
	}

}
 
void insere_valores(lista **inicio, lista **fim){  //insere valores na lista
	lista *No;
	char str[30];
	int n;

	do{
		printf("digite a string: ");
		scanf("%s",str);

		aloca(&No,str);

		insere(inicio,fim,&No);

		printf("\ndigite 0 para parar ou 1 para continuar: ");
		scanf("%d",&n);


	}while(n != 0);

}

int strings_vizinhas(lista *inicio, lista *fim,char *str, vizinhas *vizinha){  //busca um valor  e devove uma estrutura com o valor
	int flag = 0;

	lista *ant,*aux;
	
	ant = NULL;
	aux = inicio;

	
	
	if ( strcmp(str , (*inicio).str ) == 0  ){  //se a sritrig que buscamos estiver no inicio
		aux = aux->prox; 
		strcpy(vizinha->prox,aux->str); //devolve a string proxima a ela
		strcpy(vizinha->ant,"");
		flag = 1;
		
	}else{   // se o valor nao foi inserido no inicio nem no fim
		
		while( strcmp(str , aux->str) > 0){ // busca a posisao no qual vai ser inserido o valor
			ant = aux;
			aux= aux->prox;

		}
		if ( strcmp(str , aux->str) == 0){
			
			if(aux == fim){      //se a sritrig que buscamos estiver no fim
				strcpy(vizinha->prox,"");
				strcpy(vizinha->ant,ant->str); //devolve a string proxima a ela
				flag = 2;
			
			}else{  						// se o valor tiver entre o inicio e o fim da lista
				aux = aux->prox;		
				strcpy(vizinha->prox,aux->str); //devolve a string proxima a ela e a anterior a ela
				strcpy(vizinha->ant,ant->str);
				flag = 3;
			}
			
		}
	}

	return flag; //indica se string foi encontrada e sua vizinhas

}

int remover(lista **inicio, lista **fim, char *str){ //remove um valor da lista
	int flag = 0;

	lista *ant,*aux;
	
	ant = NULL;
	aux = *inicio;

	if(*inicio != NULL){  // se o inicio nao for nulo

		if ( strcmp((**inicio).str , str) == 0 ){ // remove o valor se o valor tiver no inicio da fila
			*inicio = (**inicio).prox;  // e muda o inicio da fila
			flag = 1;
			free(aux);
		
		}else{ // se o valor não estiver no inicio

			while(aux != NULL && strcmp(str , aux->str) > 0){ // percorre a lista buscando a posisao do valor que vai ser removido da lista
				ant = aux;
				aux = aux->prox;
			}
			
			if ( strcmp(str , aux->str) == 0){  // se a posição encontrada anteriormente for a posição do valor
				                      // que queremos remover
				if(aux == *fim){      //entao se o valor estiver no fim remove o valor e muda o fim da lista
					ant->prox = NULL;  
					*fim = ant;
					free(aux);
				
				}else{  						// se o valor tiver entre o inicio e o fim da lista
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

int consoantes(char l){  //recebe um caracter e devolve 1 se ele for consoante
	int i;				//e devolve 0 se ele nao for consoante
	char c[] = "aeiou" ;

	for (i = 0; i < strlen(c); ++i){

		if ( (tolower(l) == c[i] ) || (  tolower(l) <96 || tolower(l) > 122 ) ){
			return 0;
		}
	}

	return 1;

}

void lista_consoante(lista *inicio , lista **i_LC , lista **f_LC){ ////devolve lista de strings que iniciam com vogais
	lista *aux,*No;
	
	aux = inicio;

	while(aux != NULL){ //perrcorre a lista principal

		if (consoantes(aux->str[0] ) == 1){ //se o primeiro caracter string for consoante
			aloca(&No,aux->str); 	//aloca a string no NO
			insere(i_LC,f_LC,&No); //e insere lista LC lista de strings que iniciam com consoantes
		}
		
		aux = aux->prox;
		
	}

}
void lista_vogais(lista *inicio , lista **i_LV , lista **f_LV){ //devolve lista de strings que iniciam com vogais
	lista *aux,*No;
	
	aux = inicio;

	while(aux != NULL){ //perrcorre a lista principal

		if (consoantes(aux->str[0] ) == 0){ //se o primeiro caracter string for vogal
			aloca(&No,aux->str);  //aloca a string no NO
			insere(i_LV,f_LV,&No); //e insere lista LV lista de strings que iniciam com vogais
		}
		
		aux = aux->prox;
		
	}

}

void lista_ordem_tam(lista *inicio , lista **i_LV , lista **f_LV){

	lista *aux,*No;
	
	aux = inicio;

	while(aux != NULL){ //perrcorre a lista principal

		aloca(&No,aux->str), //aloca o valor da lista principal
		insere_por_tam(i_LV,f_LV,&No);//e insere na lista ordenando as strings por seu tamanhos
		
		
		aux = aux->prox; //passa para o proximo elemento
		
	}


}


void menu(int *op){ //imprime menu
	
	printf("\n1- Inserir strings lista\n");
	printf("2- imprimir strings da lista principal\n");
	printf("3- gerar lista de strings que inicia com consoantes \n");
	printf("4- gerar lista de strings que inicia com vogais \n");
	printf("5- gerar lista de strings ordenadas pelo tamanho \n");
	printf("6- imprimir strings vizinhas \n");
	printf("7- sair \n");
	printf("\ndigite opcao: ");
	scanf("%d",op);
}


int main(){
	
	lista *inicio,*fim; //lista de strings principal
	lista *i_LC,*f_LC; //lista palavras que iniciam com consoantes
	lista *i_LV,*f_LV; //lista palavras que iniciam com vogais
	lista *i_LT,*f_LT; //lista de strings ordenadas por tamnanho

	vizinhas str_vizinhas; //recebe strings vizinhas

	int N,op=1,flag;
	char str[30];
	
	inicia(&inicio,&fim);
	inicia(&i_LC,&f_LC);
	inicia(&i_LV,&f_LV);
	

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
					printf("ERRO: lista principal vazia\n");
				}	 
				
				
				break;
			
			case 3:
				if (inicio != NULL){
					lista_consoante(inicio,&i_LC,&f_LC); //recebe uma lista e devolve a lista com strings consoantes
					
					if (i_LC != NULL){
						printf("\nlista strings que iniciam com consoantes:\n");
						imprimir(i_LC);
					}else{
						printf("\nERRO: lista de entrada nao possui strings que iniciam com consoantes\n");
					}

				}else{
					printf("ERRO: lista principal vazia\n");
				}
				
				break;

			case 4:
				if (inicio != NULL){  
					printf("\nlista strings que iniciam com vogais:\n");
					lista_vogais(inicio,&i_LV,&f_LV);  //recebe uma lista e devolve a lista com strings vogais
					
					if (i_LV != NULL){
						imprimir(i_LV);
					}else{
						printf("\nERRO: lista de entrada nao possui strings que iniciam com vogais\n");
					}
				
				}else{
					printf("ERRO: lista principal vazia\n");
				}

				break;


			case 5:
				if (inicio != NULL){
					inicia(&i_LT,&f_LT);
					lista_ordem_tam(inicio,&i_LT,&f_LT); //recebe uma lista e devolve a lista com strings ordenadas por tamanho
					printf("\nlista strings ordenadas por tamnanho:\n");
					imprimir(i_LT);
				
				}else{
					printf("ERRO: lista principal vazia\n");
				}

				break;

			
			case 6:
				if (inicio != NULL){
					printf("digite a string: ");
					scanf("%s",str);

					flag = strings_vizinhas(inicio,fim,str,&str_vizinhas); //devolve strings vizinhas

					if (flag == 1){ //flag ==1 quer dizer que a string bucada esta no inicio entao 
									// sua vizinha vai ser a que esta proxima a ela
						printf("\n string vizinha a %s: %s \n",str,str_vizinhas.prox);
					
					}else if (flag == 2){//flag ==2 quer dizer que a string bucada esta no fim entao 
										// sua vizinha vai ser a que esta anterior a ela
						printf("\n string vizinha a %s: %s \n",str,str_vizinhas.ant);
					
					}else if (flag == 3){ //flag ==1 quer dizer que a string bucada esta meio da lista 
									// suas vizinha vai ser a que esta proxima a ela e a anterior a ela
						printf("\n stringS vizinha a %s: %s e %s\n",str,str_vizinhas.ant,str_vizinhas.prox);
					}else{
						printf("ERRO! string digitada nao exite\n"); 
						          // se nao entrar nos casos anteriores quer dizer que a string nao existe
					}


				}else{
					printf("ERRO: lista principal vazia\n");
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